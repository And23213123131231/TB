#pragma once

#include <QtCore/QByteArray>
#include <QtCore/QList>
#include <QtCore/QObject>
#include <QtNetwork/QSslError>

QT_FORWARD_DECLARE_CLASS(QWebSocketServer)
QT_FORWARD_DECLARE_CLASS(QWebSocket)

class TicketsDatabase;
/*!
 * \brief The TicketServer class
 * The root class of Web Socket Server
 * Using for connections handling and database communication
 */
class TicketServer : public QObject {
    Q_OBJECT
public:
    /*!
     * \brief TicketServer
     * \param port port forlistining
     * \param parent parent object
     */
    explicit TicketServer(quint16 port, QObject* parent = nullptr);
    ~TicketServer() override;

    /*!
     * \brief init server initialization (ssl initialization, port opening,...)
     * \return
     */
    bool init();

private Q_SLOTS:
    /*!
     * \brief clientConnect New client connecting
     */
    void clientConnected();

    /*!
     * \brief clientDisconnected Exist client disconnecting
     */
    void clientDisconnected();

    /*!
     * \brief onSslErrors Ssl error has occurred
     * \param errors errors list
     */
    void onSslErrors(const QList<QSslError>& errors);

private:
    QWebSocketServer* m_server;
    QSet<QWebSocket*> m_clients;
    TicketsDatabase* m_database;
    quint16 m_port;
};
