#include <QtCore/QDebug>
#include <QtCore/QFile>
#include <QtNetwork/QSslCertificate>
#include <QtNetwork/QSslKey>
#include <QtWebSockets/QWebSocket>
#include <QtWebSockets/QWebSocketServer>

#include "database/TicketsDatabase.h"
#include "network/Connection.h"

#include "TicketServer.h"

TicketServer::TicketServer(quint16 port, QObject* parent)
    : QObject(parent)
    , m_server(new QWebSocketServer(QStringLiteral("SSL Echo Server"),
          QWebSocketServer::SecureMode, this))
    , m_database(new TicketsDatabase { this })
    , m_port(port)
{
}

TicketServer::~TicketServer()
{
    m_server->close();
    qDeleteAll(m_clients.begin(), m_clients.end());
}

bool TicketServer::init()
{
    {
        QFile modelJS(":/FilmTicket.js");
        if (!modelJS.open(QIODevice::ReadOnly)) {
            qWarning() << QStringLiteral("Can't tickets data file");
            return false;
        } else {
            if (!m_database->init(modelJS.readAll())) {
                return false;
            }
        }
    }

    QSslConfiguration sslConfiguration;
    QFile certFile(QStringLiteral(":/localhost.cert"));
    QFile keyFile(QStringLiteral(":/localhost.key"));

    if (!certFile.open(QIODevice::ReadOnly)) {
        qWarning() << QStringLiteral("Can't open cert file");
        return false;
    }

    if (!keyFile.open(QIODevice::ReadOnly)) {
        qWarning() << QStringLiteral("Can't open key file");
        return false;
    }

    QSslCertificate certificate(&certFile, QSsl::Pem);
    QSslKey sslKey(&keyFile, QSsl::Rsa, QSsl::Pem);

    certFile.close();
    keyFile.close();

    sslConfiguration.setPeerVerifyMode(QSslSocket::VerifyNone);
    sslConfiguration.setLocalCertificate(certificate);
    sslConfiguration.setPrivateKey(sslKey);
    m_server->setSslConfiguration(sslConfiguration);

    if (m_server->listen(QHostAddress::Any, m_port)) {
        qDebug() << "SSL Echo Server listening on port" << m_port;
        connect(m_server, &QWebSocketServer::newConnection, this,
            &TicketServer::clientConnected);

        connect(m_server, &QWebSocketServer::sslErrors, this,
            &TicketServer::onSslErrors);

        return true;
    } else {
        qDebug() << m_server->errorString();
    }

    return false;
}

void TicketServer::clientConnected()
{
    QWebSocket* pSocket = m_server->nextPendingConnection();
    qInfo() << "Client connected:" << pSocket->peerName()
            << pSocket->peerAddress() << pSocket->origin();

    Connection* client = new Connection(pSocket);

    connect(client, &Connection::theatersRequested, this, [this, client]() {
        client->sendTheaters(m_database->theaters());
    });

    connect(client, &Connection::moviesRequested, this, [this, client]() {
        client->sendMovies(m_database->movies());
    });

    connect(client, &Connection::ticketsRequested, this, [this, client](int theaterId, int movieId) {
        client->sendTickets(m_database->theaterMovieTickets(theaterId, movieId));
    });

    connect(client, &Connection::bookingRecived, this, [this, client](const Data::Tickets& tickets) {
        client->sendBookingConfirmation(m_database->bookTickets(tickets));
        // update user tickets info
        client->sendTickets(m_database->theaterMovieTickets(tickets.theaterId, tickets.movieId));
    });

    m_clients.insert(pSocket);
    connect(pSocket, &QWebSocket::disconnected, this,
        &TicketServer::clientDisconnected);
}

void TicketServer::clientDisconnected()
{
    QWebSocket* pSocket = qobject_cast<QWebSocket*>(sender());
    if (pSocket) {
        qInfo() << "Client disconnected:" << pSocket->peerName()
                << pSocket->peerAddress() << pSocket->origin();

        m_clients.remove(pSocket);
        pSocket->deleteLater();
    }
}

void TicketServer::onSslErrors(const QList<QSslError>& errors)
{
    qInfo() << "Ssl errors occurred " << errors;
}
