#pragma once
#include <QObject>

#include "tools/DataProcessor.h"

QT_FORWARD_DECLARE_CLASS(QWebSocket)

/*!
 * \brief The Connection class
 * Represent a single client connection
 * Creting on incoming connection
 * Using for netwok communication
 */
class Connection : public QObject, public DataProcessor {
    Q_OBJECT

public:
    /*!
     * \brief Connection
     * \param parent parent object
     */
    explicit Connection(QWebSocket* parent = nullptr);

    /*!
     * \brief sendTheaters
     * \param theaters all the theaters
     */
    void sendTheaters(const QList<Data::Theater>& theaters);

    /*!
     * \brief sendMovies
     * \param movies all the movies
     */
    void sendMovies(const QList<Data::Movie>& movies);

    /*!
     * \brief sendTickets
     * \param movies tickets for given theater and movie
     */
    void sendTickets(const Data::Tickets& tickets);

    /*!
     * \brief sendBookingConfirmation send booking result
     * \param result true if booking was successful
     */
    void sendBookingConfirmation(bool result);
signals:
    /*!
     * \brief moviesRequested
     */
    void moviesRequested();

    /*!
     * \brief theatersRequested
     */
    void theatersRequested();

    /*!
     * \brief ticketsRequested resuest tickets for given theater id and movie id
     * \param theaterId
     * \param movieId
     */
    void ticketsRequested(quint32 theaterId, quint32 movieId);

    /*!
     * \brief bookingRecived request booking
     */
    void bookingRecived(const Data::Tickets&);

protected:
    void onMovieRecived(const Data::Movie&) override;
    void onTheaterRecived(const Data::Theater&) override;
    void onTicketsRecived(const Data::Tickets&) override;
    void onReuqestMoviesRecived() override;
    void onReuqestTheatersRecived() override;
    void onMoviePackRecived(const QList<Data::Movie>&) override;
    void onReuqestBookingRecived(const Data::Tickets&) override;
    void onBookingResultRecived(bool) override;
    void onTheaterPackRecived(const QList<Data::Theater>&) override;
    void onReuqestTicketsRecived(quint32 theaterId, quint32 movieId) override;

private slots:
    /*!
     * \brief processBinaryMessage
     * \param message incoming binary message
     */
    void processBinaryMessage(const QByteArray& message);

private:
    QWebSocket* m_socket;
};
