#include <QTimer>
#include <QWebSocket>

#include "tools/DataStructures.h"

#include "Client.h"

Client::Client(QUrl&& url, QObject* parent)
    : QObject(parent)
    , DataProcessor()
    , m_serverUrl(url)
    , m_webSocket(new QWebSocket {})
{
    connect(m_webSocket, &QWebSocket::connected, this, &Client::connected);
    connect(m_webSocket, &QWebSocket::disconnected, this, &Client::disconnected);
    connect(m_webSocket, &QWebSocket::binaryMessageReceived, this, [this](QByteArray message) {
        if (!DataProcessor::parseMessage(message)) {
            qDebug() << "DataProcessor::parseMessage disconnect";
            m_webSocket->close(QWebSocketProtocol::CloseCodeWrongDatatype);
        }
    });

    connect(m_webSocket, QOverload<const QList<QSslError>&>::of(&QWebSocket::sslErrors), this,
        [this](const QList<QSslError>& errors) {
            qDebug() << "SslEchoClient::onSslErrors: " << errors;

            // TODO: implement this part
            // WARNING: Never ignore SSL errors in production code.
            // The proper way to handle self-signed certificates is to add a custom root
            // to the CA store.

            m_webSocket->ignoreSslErrors();
        });
}

Client::~Client()
{
    m_webSocket->deleteLater();
}

void Client::connectToServer()
{
    m_webSocket->open(m_serverUrl);
    emit transferStatus(true);
}

void Client::requestTickets(int theaterId, int movieId)
{
    QByteArray buff;
    QDataStream stream(&buff, QIODevice::WriteOnly);
    NetworkData::ReuqestTickets request;
    request.theaterId = theaterId;
    request.movieId = movieId;
    request.writeStream(stream);
    m_webSocket->sendBinaryMessage(buff);
    emit transferStatus(true);
}

void Client::bookTickets(const Data::Tickets& tickets)
{
    QByteArray buff;
    QDataStream stream(&buff, QIODevice::WriteOnly);
    NetworkData::ReuqestBooking request;
    request.data = tickets;
    request.writeStream(stream);
    m_webSocket->sendBinaryMessage(buff);
    emit transferStatus(true);
}

void Client::connected()
{
    // request movies
    {
        QByteArray buff;
        QDataStream stream(&buff, QIODevice::WriteOnly);
        NetworkData::ReuqestMovies().writeStream(stream);
        m_webSocket->sendBinaryMessage(buff);
    }

    // request theaters
    {
        QByteArray buff;
        void messageSended();
        void messageRecived();
        QDataStream stream(&buff, QIODevice::WriteOnly);
        NetworkData::ReuqestTheaters().writeStream(stream);
        m_webSocket->sendBinaryMessage(buff);
    }
}

void Client::disconnected()
{
    qDebug() << "Client disconnected try to reconnect";
    QTimer::singleShot(3000, this, [this]() {
        connectToServer();
    });
    emit transferStatus(true);
}

void Client::onMovieRecived(const Data::Movie& movie)
{
    emit transferStatus(false);
}

void Client::onTheaterRecived(const Data::Theater&)
{
    emit transferStatus(false);
}

void Client::onTicketsRecived(const Data::Tickets& tickets)
{
    emit ticketsRecived(tickets);
    emit transferStatus(false);
}

void Client::onReuqestMoviesRecived()
{
    qDebug() << "Client::onReuqestMoviesRecived disconnect";
    // client does not handle this information
    m_webSocket->close(QWebSocketProtocol::CloseCodeWrongDatatype);
}

void Client::onReuqestTheatersRecived()
{
    qDebug() << "Client::onReuqestTheatersRecived disconnect";
    // client does not handle this information
    m_webSocket->close(QWebSocketProtocol::CloseCodeWrongDatatype);
}

void Client::onReuqestBookingRecived(const Data::Tickets&)
{
    qDebug() << "Client::onReuqestBookingRecived disconnect";
    // client does not handle this information
    m_webSocket->close(QWebSocketProtocol::CloseCodeWrongDatatype);
}

void Client::onMoviePackRecived(const QList<Data::Movie>& pack)
{
    emit moviePackRecived(pack);
    emit transferStatus(false);
}

void Client::onBookingResultRecived(bool result)
{
    emit bookingResult(result);
    emit transferStatus(false);
}

void Client::onTheaterPackRecived(const QList<Data::Theater>& pack)
{
    emit thaterPackRecived(pack);
    emit transferStatus(false);
}

void Client::onReuqestTicketsRecived(quint32 theaterId, quint32 movieId)
{
    qDebug() << "Client::onReuqestTicketsRecived disconnect";
    // client does not handle this information
    m_webSocket->close(QWebSocketProtocol::CloseCodeWrongDatatype);
}
