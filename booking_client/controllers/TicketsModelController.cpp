#include <QDebug>
#include <QUrl>

#include "StackViewController.h"

#include "TicketsModelController.h"

TicketsModelController* TicketsModelController::s_movies(nullptr);

TicketsModelController::TicketsModelController(QObject* parent)
    : QAbstractListModel(parent)
{
    s_movies = this;
}

TicketsModelController::~TicketsModelController()
{
    s_movies = nullptr;
}

QHash<int, QByteArray> TicketsModelController::TicketsModelController::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[SeatName] = "seatName";
    roles[SeatStatus] = "seatStatus";
    return roles;
}

TicketsModelController* TicketsModelController::get()
{
    return s_movies;
}

void TicketsModelController::updateModel(const Data::Tickets& tickets)
{
    if (tickets.movieId == m_movieId && tickets.theaterId == m_thaeterId) {
        beginResetModel();
        m_tickets = tickets;
        endResetModel();
        emit ticketsChanged();
        checkActiveSelection();
    }
}

QVariant TicketsModelController::data(const QModelIndex& index, int role) const
{
    QVariant value;

    if (index.isValid()) {
        if (role > Qt::UserRole) {
            //            int idx =  + index.row() % m_tickets.colCount;

            switch (role) {
            case SeatName:
                value = char('A' + index.row() / m_tickets.colCount) + QString::number(index.row() % m_tickets.colCount);
                break;
            case SeatStatus:
                if (auto userBooking = m_bookedTickets.find({ m_thaeterId, m_movieId });
                    userBooking != m_bookedTickets.end() && userBooking.value().end() != userBooking.value().constFind(index.row())) {
                    value = TicketStatus::BookedByUser;
                } else {
                    switch (m_tickets.ticketsStatus[index.row()]) {
                    case Data::Tickets::Status::Free:
                        value = TicketStatus::Free;
                        break;
                    case Data::Tickets::Status::Booked:
                        value = TicketStatus::Booked;
                        break;
                    case Data::Tickets::Status::TryBook:
                        value = TicketStatus::TryBook;
                        break;
                    default:
                        break;
                    }
                }
                break;
            default:
                break;
            }
        }
    }
    return value;
}

int TicketsModelController::rowCount(const QModelIndex& parent) const
{
    return m_tickets.ticketsStatus.count();
}

int TicketsModelController::columnCount(const QModelIndex& parent) const
{
    return 1;
}

int TicketsModelController::movieId() const
{
    return m_movieId;
}

void TicketsModelController::setMovieId(int id)
{
    if (id != m_movieId) {
        m_movieId = id;
        emit movieIdChanged();
        requestNewTickets();
    }
}

int TicketsModelController::theaterId() const
{
    return m_thaeterId;
}

void TicketsModelController::setTheaterId(int id)
{
    if (id != m_thaeterId) {
        m_thaeterId = id;
        emit theaterIdChanged();
        requestNewTickets();
    }
}

int TicketsModelController::ticketsRowsCount() const
{
    return m_tickets.rowCount;
}

int TicketsModelController::ticketsColumnsCount() const
{
    return m_tickets.colCount;
}

void TicketsModelController::tryBook(int index)
{
    auto& bookStatus = m_tickets.ticketsStatus[index];
    if (Data::Tickets::Status::Free == bookStatus) {
        bookStatus = Data::Tickets::Status::TryBook;
        emit dataChanged(createIndex(index, 0), createIndex(index, 0));
    } else if (Data::Tickets::Status::TryBook == bookStatus) {
        bookStatus = Data::Tickets::Status::Free;
        emit dataChanged(createIndex(index, 0), createIndex(index, 0));
    }

    checkActiveSelection();
}

void TicketsModelController::confirmBooking()
{
    if (m_hasSelection) {
        emit ticketsConfirmationRequest(m_tickets);
    }
}

void TicketsModelController::confirmationResult(bool result)
{
    if (result) {
        for (auto seatIdx = 0; seatIdx < m_tickets.ticketsStatus.size(); ++seatIdx) {
            if (Data::Tickets::Status::TryBook == m_tickets.ticketsStatus[seatIdx]) {
                m_bookedTickets[{ m_thaeterId, m_movieId }].insert(seatIdx);
            }
        }
    } else {
        StackViewController::get()->showMessage(QStringLiteral("Booking failed. Try again with another seats"));
    }
}

bool TicketsModelController::hasSelection() const
{
    return m_hasSelection;
}

void TicketsModelController::requestNewTickets()
{
    if (0 != m_movieId && 0 != m_thaeterId) {
        emit requestTickets(m_thaeterId, m_movieId);
    }

    beginResetModel();
    m_tickets.ticketsStatus.clear();
    endResetModel();
}

void TicketsModelController::checkActiveSelection()
{
    bool hasSelection = false;
    for (const auto& ticket : m_tickets.ticketsStatus) {
        if (Data::Tickets::Status::TryBook == ticket) {
            hasSelection = true;
            break;
        }
    }

    if (hasSelection != m_hasSelection) {
        m_hasSelection = hasSelection;
        emit hasSelectionChanged();
    }
}
