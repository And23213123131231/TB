#pragma once

#include <QAbstractListModel>
#include <QObject>
#include <QStack>
#include <QVariantMap>

#include "tools/DataStructures.h"

/*!
 * \brief The TicketsModelController class
 * This class represents the available tickets for given theater and movie
 */
class TicketsModelController : public QAbstractListModel {
    Q_OBJECT

    Q_PROPERTY(int movieId READ movieId WRITE setMovieId NOTIFY movieIdChanged)
    Q_PROPERTY(int theaterId READ theaterId WRITE setTheaterId NOTIFY theaterIdChanged)

    Q_PROPERTY(int ticketsRowsCount READ ticketsRowsCount NOTIFY ticketsChanged)
    Q_PROPERTY(int ticketsColumnsCount READ ticketsColumnsCount NOTIFY ticketsChanged)

    Q_PROPERTY(bool hasSelection READ hasSelection NOTIFY hasSelectionChanged)

    enum MovieRoles {
        SeatName = Qt::UserRole + 1,
        SeatStatus
    };

public:
    enum TicketStatus {
        Free = 0,
        Booked,
        TryBook,
        BookedByUser
    };
    Q_ENUM(TicketStatus);

    /*!
     * \brief TicketsModelController
     * \param parent parent object
     */
    TicketsModelController(QObject* parent = nullptr);
    ~TicketsModelController() override;

    QHash<int, QByteArray> roleNames() const override;

    /*!
     * \brief get Get singletone object
     * \return instance
     */
    static TicketsModelController* get();

    void updateModel(const Data::Tickets& tickets = Data::Tickets());

    QVariant data(const QModelIndex& index, int role) const override;

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;

    /*!
     * \brief movieId
     * \return current movieId
     */
    int movieId() const;

    /*!
     * \brief setMovieId
     * \param id current  movie id
     */
    void setMovieId(int id);

    /*!
     * \brief theaterId
     * \return current theater id
     */
    int theaterId() const;

    /*!
     * \brief setTheaterId set current theater id
     * \param id
     */
    void setTheaterId(int id);

    /*!
     * \brief ticketsRowsCount count of the rows for preview
     * \return rows count
     */
    int ticketsRowsCount() const;

    /*!
     * \brief ticketsRowsCount count of the columns for preview
     * \return columns count
     */
    int ticketsColumnsCount() const;

    /*!
     * \brief tryBook mark the seat as booked by the user. No information will be sent to the server until confirmBooking() will be called
     * \param index seat index
     */
    Q_INVOKABLE void tryBook(int index);

    /*!
     * \brief confirmBooking send request to server
     */
    Q_INVOKABLE void confirmBooking();

    /*!
     * \brief confirmationResult tickets request result
     * \param result true = booking successful, false = booking fail
     */
    void confirmationResult(bool result);

    /*!
     * \brief hasSelection
     * \return true is  user has one or more selected seats
     */
    bool hasSelection() const;

signals:
    void movieIdChanged();
    void theaterIdChanged();
    void ticketsChanged();
    void requestTickets(int theaterId, int movieId);
    void ticketsConfirmationRequest(const Data::Tickets&);
    void hasSelectionChanged();

private:
    static TicketsModelController* s_movies;
    Data::Tickets m_tickets;
    int m_movieId = 0;
    int m_thaeterId = 0;
    QHash<QPair<int, int>, QSet<int>> m_bookedTickets;
    bool m_hasSelection = false;

    /*!
     * \brief requestNewTickets this method shoul be called after movieId or theaterId
     * It will emit signal to reload the tickets
     */
    void requestNewTickets();

    /*!
     * \brief checkActiveSelection check if user has selection and change corresponded variable
     */
    void checkActiveSelection();
};
