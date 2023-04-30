#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

#include "../database/TicketsDatabase.h"

#include "TicketsDatabase_Test.h"

namespace Test {
void TicketsDatabase_Test::initTestCase()
{
    m_database.reset(new TicketsDatabase {});
}

void TicketsDatabase_Test::testInitDatabase()
{
    QByteArray initData = R"(
    {
        "movies": [{
                "id": 1,
                "name": "name1",
                "score": 1,
                "critics": "critics1",
                "synopsis": "synopsis1",
                "starring": "starring1",
                "directed": "directed1"
            }
        ],
        "theaters": [{
                "id" : 1,
                "name": "name1",
                "movies": [1]
            }
        ]
    })";
    m_database->init(initData);

    QVERIFY(m_database->movies().size() == 1);
    QVERIFY(m_database->theaters().size() == 1);

    const auto& movie = m_database->movies().first();
    QVERIFY(movie.id == 1);
    QVERIFY(movie.name == "name1");
    QVERIFY(movie.score == 1);
    QVERIFY(movie.critics == "critics1");
    QVERIFY(movie.synopsis == "synopsis1");
    QVERIFY(movie.starring == "starring1");
    QVERIFY(movie.directed == "directed1");

    const auto& theater = m_database->theaters().first();
    QVERIFY(theater.id == 1);
    QVERIFY(theater.name == "name1");
    QSet<quint32> movies;
    movies << 1;
    QVERIFY(theater.movies == movies);

    const auto& tickets = m_database->theaterMovieTickets(1, 1);
    QVERIFY(tickets.ticketsStatus.size() == tickets.rowCount * tickets.colCount);

    for (const auto& seatStatus : tickets.ticketsStatus) {
        QVERIFY(seatStatus == Data::Tickets::Status::Free);
    }
}

void TicketsDatabase_Test::testTicketBooking()
{
    auto changeTicketStatus = [this](Data::Tickets::Status status) {
        auto changedTickets = m_database->theaterMovieTickets(1, 1);
        for (auto& seatStatus : changedTickets.ticketsStatus) {
            seatStatus = status;
        }

        auto ticketsCurrentStatus = m_database->theaterMovieTickets(1, 1);

        m_database->bookTickets(changedTickets);
        if (Data::Tickets::Status::TryBook != status) {
            // shouldn't change, compare saved tickets with actual
            QVERIFY(ticketsCurrentStatus.ticketsStatus == m_database->theaterMovieTickets(1, 1).ticketsStatus);
        } else {
            // should change, compare actual
            ticketsCurrentStatus = m_database->theaterMovieTickets(1, 1);
            for (const auto& status : ticketsCurrentStatus.ticketsStatus) {
                QVERIFY(status == Data::Tickets::Status::Booked);
            }
        }
    };

    changeTicketStatus(Data::Tickets::Status::Free);
    changeTicketStatus(Data::Tickets::Status::Booked);
    changeTicketStatus(Data::Tickets::Status::TryBook);
}

} // namespace Test
