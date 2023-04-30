#include <algorithm>

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

#include "TicketsDatabase.h"

TicketsDatabase::TicketsDatabase(QObject* parent)
    : QObject { parent }
{
}

bool TicketsDatabase::init(const QByteArray& data)
{
    QJsonParseError error;
    QJsonDocument document = QJsonDocument::fromJson(data, &error);

    if (error.error != QJsonParseError::NoError) {
        qWarning() << error.errorString();
        return false;
    }

    auto assignString = [](QString& out, const QString& searchKey, const QJsonObject& obj) -> bool {
        if (const auto& it = obj.find(searchKey); it != obj.end()) {
            out = it.value().toString();
            return true;
        }
        return false;
    };

    auto assignInt = [](int& out, const QString& searchKey, const QJsonObject& obj) -> bool {
        if (const auto& it = obj.find(searchKey); it != obj.end()) {
            out = it.value().toInt();
            return true;
        }
        return false;
    };

    QJsonObject root = document.object();
    const auto& moviesRoot = root.find(QStringLiteral("movies"));
    if (root.end() != moviesRoot) {
        QJsonArray movies = moviesRoot->toArray();
        for (const auto& movie : movies) {
            const QJsonObject movieObj = movie.toObject();

            Data::Movie tmp;

            auto insertPos = m_movies.end();
            if (!assignInt(tmp.id, QStringLiteral("id"), movieObj)) {
                qWarning() << "Missed movie Id";
                return false;
            } else if (tmp.id <= 0) {
                qWarning() << "Movie id is not valid " << tmp.id;
                return false;
            } else if (insertPos = std::lower_bound(m_movies.begin(), m_movies.end(), tmp);
                       insertPos != m_movies.end() && insertPos->id == tmp.id) {
                qWarning() << "Movie id duplication " << tmp.id;
                return false;
            }

            assignInt(tmp.score, QStringLiteral("score"), movieObj);
            assignString(tmp.name, QStringLiteral("name"), movieObj);
            assignString(tmp.critics, QStringLiteral("critics"), movieObj);
            assignString(tmp.synopsis, QStringLiteral("synopsis"), movieObj);
            assignString(tmp.starring, QStringLiteral("starring"), movieObj);
            assignString(tmp.directed, QStringLiteral("directed"), movieObj);
            m_movies.insert(insertPos, std::move(tmp));
        }
    }

    const auto& theatersRoot = root.find(QStringLiteral("theaters"));
    if (root.end() != theatersRoot) {
        QJsonArray theatersArray = theatersRoot->toArray();
        for (const auto& theater : theatersArray) {
            const QJsonObject theaterObject = theater.toObject();

            Data::Theater tmp;

            auto insertPos = m_theaters.end();
            if (!assignInt(tmp.id, QStringLiteral("id"), theaterObject)) {
                qWarning() << "Missed theater Id";
                return false;
            } else if (tmp.id <= 0) {
                qWarning() << "Theater id is not valid " << tmp.id;
                return false;
            } else if (insertPos = std::lower_bound(m_theaters.begin(), m_theaters.end(), tmp);
                       insertPos != m_theaters.end() && insertPos->id == tmp.id) {
                qWarning() << "Theater id duplication " << tmp.id;
                return false;
            }

            assignString(tmp.name, QStringLiteral("name"), theaterObject);

            if (const auto& it = theaterObject.find("movies"); theaterObject.end() != it) {
                QJsonArray movies = it->toArray();
                for (const auto& movie : movies) {
                    tmp.movies.insert(movie.toInt());
                }
            }

            m_theaters.insert(insertPos, std::move(tmp));
        }
    }

    std::sort(m_theaters.begin(), m_theaters.end());
    std::sort(m_movies.begin(), m_movies.end());

    for (const auto& theater : m_theaters) {
        for (const auto& movie : theater.movies) {
            Data::Tickets tickets;
            tickets.theaterId = theater.id;
            tickets.movieId = movie;
            tickets.rowCount = 5;
            tickets.colCount = 4;
            tickets.ticketsStatus.resize(tickets.rowCount * tickets.colCount, Data::Tickets::Status::Free);
            m_tickets.push_back(std::move(tickets));
        }
    }
    std::sort(m_tickets.begin(), m_tickets.end());
    return true;
}

Data::Tickets TicketsDatabase::theaterMovieTickets(int theaterId, int movieId)
{
    Data::Tickets tickets;
    tickets.theaterId = theaterId;
    tickets.movieId = movieId;

    if (auto theaterIt = std::lower_bound(m_tickets.begin(), m_tickets.end(), tickets); theaterIt != m_tickets.end() && *theaterIt == tickets) {
        tickets = *theaterIt;
    }
    return tickets;
}

bool TicketsDatabase::bookTickets(const Data::Tickets& tickets)
{
    if (auto theaterIt = std::lower_bound(m_tickets.begin(), m_tickets.end(), tickets); theaterIt != m_tickets.end() && *theaterIt == tickets) {
        bool bookingConfirmation = true;
        auto currentSeatsState = theaterIt->ticketsStatus;
        for (auto seatIdx = 0; seatIdx < tickets.ticketsStatus.size(); ++seatIdx) {
            if (Data::Tickets::Status::TryBook == tickets.ticketsStatus[seatIdx]) {
                if (seatIdx >= currentSeatsState.size() || Data::Tickets::Status::Free != currentSeatsState[seatIdx]) {
                    bookingConfirmation = false;
                    break;
                } else {
                    currentSeatsState[seatIdx] = Data::Tickets::Status::Booked;
                }
            }
        }

        if (bookingConfirmation) {
            theaterIt->ticketsStatus = currentSeatsState;
        }
        return bookingConfirmation;
    }
    return false;
}
