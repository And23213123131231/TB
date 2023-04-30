#include "Connection.h"

#include <QDataStream>
#include <QWebSocket>

#include "tools/DataStructures.h"

namespace {
const int OperationDisconnectTimeout = 3000;
}

Connection::Connection(QWebSocket* parent)
    : QObject { parent }
    , DataProcessor()
    , m_socket(parent)
{
    connect(m_socket, &QWebSocket::binaryMessageReceived, this, &Connection::processBinaryMessage);
}

void Connection::sendTheaters(const QList<Data::Theater>& theaters)
{
    if (QByteArray buff; !packListToMessage<NetworkData::Theater>(theaters, buff) || buff.size() != m_socket->sendBinaryMessage(buff)) {
        qDebug() << "Connection::sendTheaters disconnect";
        m_socket->close(QWebSocketProtocol::CloseCodeWrongDatatype);
    }
}

void Connection::sendMovies(const QList<Data::Movie>& movies)
{
    if (QByteArray buff; !packListToMessage<NetworkData::Movie>(movies, buff) || buff.size() != m_socket->sendBinaryMessage(buff)) {
        qDebug() << "Connection::sendMovies disconnect";
        m_socket->close(QWebSocketProtocol::CloseCodeWrongDatatype);
    }
}

void Connection::sendTickets(const Data::Tickets& tickets)
{
    QByteArray buff;
    NetworkData::Tickets network;
    QDataStream stream(&buff, QIODevice::WriteOnly);

    network.data = tickets;
    if (!network.writeStream(stream) || buff.size() != m_socket->sendBinaryMessage(buff)) {
        qDebug() << "Connection::sendTickets disconnect";
        m_socket->close(QWebSocketProtocol::CloseCodeWrongDatatype);
    }
}

void Connection::sendBookingConfirmation(bool result)
{
    QByteArray buff;
    NetworkData::BookingResult network;
    network.result = result;
    QDataStream stream(&buff, QIODevice::WriteOnly);

    if (!network.writeStream(stream) || buff.size() != m_socket->sendBinaryMessage(buff)) {
        qDebug() << "Connection::sendBookingConfirmation disconnect";
        m_socket->close(QWebSocketProtocol::CloseCodeWrongDatatype);
    }
}

void Connection::onMovieRecived(const Data::Movie&)
{
    qDebug() << "Connection::onMovieRecived disconnect";
    // server does not handle this information
    m_socket->close(QWebSocketProtocol::CloseCodeWrongDatatype);
}

void Connection::onTheaterRecived(const Data::Theater&)
{
    qDebug() << "Connection::onTheaterRecived disconnect";
    // server does not handle this information
    m_socket->close(QWebSocketProtocol::CloseCodeWrongDatatype);
}

void Connection::onTicketsRecived(const Data::Tickets&)
{
}

void Connection::onReuqestMoviesRecived()
{
    emit moviesRequested();
}

void Connection::onReuqestTheatersRecived()
{
    emit theatersRequested();
}

void Connection::onMoviePackRecived(const QList<Data::Movie>&)
{
    qDebug() << "Connection::onMoviePackRecived disconnect";
    // server does not handle this information
    m_socket->close(QWebSocketProtocol::CloseCodeWrongDatatype);
}

void Connection::onReuqestBookingRecived(const Data::Tickets& data)
{
    emit bookingRecived(data);
}

void Connection::onBookingResultRecived(bool)
{
    qDebug() << "Connection::onBookingResultRecived disconnect";
    // server does not handle this information
    m_socket->close(QWebSocketProtocol::CloseCodeWrongDatatype);
}

void Connection::onTheaterPackRecived(const QList<Data::Theater>&)
{
    qDebug() << "Connection::onTheaterPackRecived disconnect";
    // server does not handle this information
    m_socket->close(QWebSocketProtocol::CloseCodeWrongDatatype);
}

void Connection::onReuqestTicketsRecived(quint32 theaterId, quint32 movieId)
{
    emit ticketsRequested(theaterId, movieId);
}

void Connection::processBinaryMessage(const QByteArray& message)
{
    if (!DataProcessor::parseMessage(message)) {
        qDebug() << "Connection::processBinaryMessage disconnect";
        m_socket->close(QWebSocketProtocol::CloseCodeWrongDatatype);
    }
}
