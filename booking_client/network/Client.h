#pragma once

#include <QObject>
#include <QUrl>

#include "tools/DataProcessor.h"

QT_FORWARD_DECLARE_CLASS(QWebSocket)

/*!
 * \brief The Client class
 * This class is providing methods for server communication
 */
class Client : public QObject, public DataProcessor {
    Q_OBJECT

public:
    /*!
     * \brief Client
     * \param url Web socket server url, such as wss://localhost:1234
     * \param parent parent object
     */
    explicit Client(QUrl&& url, QObject* parent = nullptr);
    ~Client() override;

    /*!
     * \brief connectToServer Connect to given server
     * !Asynk task
     * This method connecting client to server.
     * It will try to connect to a server endless if server is not responding or until it will not be interrupted
     */
    void connectToServer();

    /*!
     * \brief requestTickets sent tickets request to server
     * \param theaterId theater id
     * \param movieId movie id
     */
    void requestTickets(int theaterId, int movieId);

    /*!
     * \brief bookTickets send booking request to server
     * \param tickets tickets
     */
    void bookTickets(const Data::Tickets& tickets);

private slots:
    /*!
     * \brief connected
     * This method will be called after succesfull connection
     */
    void connected();

    /*!
     * \brief disconnected This method will be called after disconnecton or
     * if the server does not respond for a long time
     */
    void disconnected();

signals:
    void thaterPackRecived(const QList<Data::Theater>&);
    void moviePackRecived(const QList<Data::Movie>&);
    void ticketsRecived(const Data::Tickets&);
    void bookingResult(bool);

    /*!
     * \brief transferStatus indicate if client has active transaction (workaround until message queue with id doesn't finished)
     * \param transfer
     */
    void transferStatus(bool transfer, const QString reason = "");

protected:
    void onMovieRecived(const Data::Movie&) override;
    void onTheaterRecived(const Data::Theater&) override;
    void onTicketsRecived(const Data::Tickets&) override;
    void onReuqestMoviesRecived() override;
    void onReuqestTheatersRecived() override;
    void onReuqestBookingRecived(const Data::Tickets&) override;
    void onMoviePackRecived(const QList<Data::Movie>&) override;
    void onBookingResultRecived(bool) override;
    void onTheaterPackRecived(const QList<Data::Theater>&) override;
    void onReuqestTicketsRecived(quint32 theaterId, quint32 movieId) override;

private:
    const QUrl m_serverUrl;
    QWebSocket* m_webSocket;
    quint64 m_connectionAttempt = 0;
};
