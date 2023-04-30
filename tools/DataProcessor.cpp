#include <QDebug>

#include "DataProcessor.h"

bool DataProcessor::parseMessage(const QByteArray& message)
{
    using namespace NetworkData;

    QDataStream stream(message);

    while (!stream.atEnd()) {
        INetworkDataSctructure::DataType type = INetworkDataSctructure::getDataType(stream);
        switch (type) {
        case INetworkDataSctructure::DataType::Movie: {
            Movie movie;
            if (movie.readStream(stream)) {
                onMovieRecived(movie.data);
            } else {
                return false;
            }
            break;
        }
        case INetworkDataSctructure::DataType::Theater: {
            Theater theater;
            if (theater.readStream(stream)) {
                onTheaterRecived(theater.data);
            } else {
                return false;
            }
            break;
        }
        case INetworkDataSctructure::DataType::Tickets: {
            Tickets tickets;
            if (tickets.readStream(stream)) {
                onTicketsRecived(tickets.data);
            } else {
                return false;
            }
            break;
        }
        case INetworkDataSctructure::DataType::ReuqestMovies: {
            ReuqestMovies moviesRequest;
            if (moviesRequest.readStream(stream)) {
                onReuqestMoviesRecived();
            } else {
                return false;
            }
            break;
        }
        case INetworkDataSctructure::DataType::ReuqestTheaters: {
            ReuqestTheaters theaterRequest;
            if (theaterRequest.readStream(stream)) {
                onReuqestTheatersRecived();
            } else {
                return false;
            }
            break;
        }
        case INetworkDataSctructure::DataType::ReuqestTickets: {
            ReuqestTickets ticketsRequest;
            if (ticketsRequest.readStream(stream)) {
                onReuqestTicketsRecived(ticketsRequest.theaterId, ticketsRequest.movieId);
            } else {
                return false;
            }
            break;
        }
        case INetworkDataSctructure::DataType::ReuqestBooking: {
            ReuqestBooking bookingRequest;
            if (bookingRequest.readStream(stream)) {
                onReuqestBookingRecived(bookingRequest.data);
            } else {
                return false;
            }
            break;
        }
        case INetworkDataSctructure::DataType::BookingResult: {
            BookingResult bookingResult;
            if (bookingResult.readStream(stream)) {
                onBookingResultRecived(bookingResult.result);
            } else {
                return false;
            }
            break;
        }
        case INetworkDataSctructure::DataType::DataPack: {
            DataPack pack;
            if (pack.readStream(stream)) {
                readPack(pack.dataSize, stream);
            } else {
                return false;
            }
            break;
        }
        default:
            return false;
        }
    }
    return true;
}

bool DataProcessor::readPack(qsizetype dataSize, QDataStream& in)
{
    using namespace NetworkData;

    const auto type = INetworkDataSctructure::getDataType(in);
    if (type == INetworkDataSctructure::DataType::Movie) {
        QList<Data::Movie> pack;
        pack.reserve(dataSize);
        for (qsizetype idx = 0; idx < dataSize; ++idx) {
            NetworkData::Movie movie;
            if (movie.readStream(in)) {
                pack.push_back(std::move(movie.data));
            } else {
                return false;
            }
        }
        emit onMoviePackRecived(pack);
    } else if (type == INetworkDataSctructure::DataType::Theater) {
        QList<Data::Theater> pack;
        pack.reserve(dataSize);
        for (qsizetype idx = 0; idx < dataSize; ++idx) {
            NetworkData::Theater movie;
            if (movie.readStream(in)) {
                pack.push_back(std::move(movie.data));
            } else {
                return false;
            }
        }
        emit onTheaterPackRecived(pack);
    } else {
        qWarning() << "Unexpected data pack type";
        return false;
    }
    return true;
}
