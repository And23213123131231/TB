#include "NetworkStructures_Test.h"

#include "../NetworkStructures.h"

namespace Test {

void NetworkStructures_Test::testMovieStruct()
{
    static const quint32 id = 1;
    static const quint32 score = 2;
    static const QString name = "name";
    static const QString critics = "critics";
    static const QString synopsis = "synopsis";
    static const QString starring = "starring";
    static const QString directed = "starring";

    NetworkData::Movie first;
    first.data.id = id;
    first.data.score = score;
    first.data.name = name;
    first.data.critics = critics;
    first.data.synopsis = synopsis;
    first.data.starring = starring;
    first.data.directed = directed;

    QByteArray buff;
    {
        QDataStream out(&buff, QIODevice::WriteOnly);
        first.writeStream(out);
    }

    NetworkData::Movie second;
    QVERIFY(second.data.id != id);
    QVERIFY(second.data.score != score);
    QVERIFY(second.data.name != name);
    QVERIFY(second.data.critics != critics);
    QVERIFY(second.data.synopsis != synopsis);
    QVERIFY(second.data.starring != starring);
    QVERIFY(second.data.directed != directed);

    {
        QDataStream in(&buff, QIODevice::ReadOnly);
        QVERIFY(NetworkData::INetworkDataSctructure::DataType::Movie == NetworkData::INetworkDataSctructure::getDataType(in));
        second.readStream(in);
    }

    QVERIFY(second.data.id == id);
    QVERIFY(second.data.score == score);
    QVERIFY(second.data.name == name);
    QVERIFY(second.data.critics == critics);
    QVERIFY(second.data.synopsis == synopsis);
    QVERIFY(second.data.starring == starring);
    QVERIFY(second.data.directed == directed);
}

void NetworkStructures_Test::testTheaterStruct()
{
    static const quint32 id = 1;
    static const QString name = "name";
    static const QSet<quint32> movies = { 1, 2, 3 };

    NetworkData::Theater first;
    first.data.id = id;
    first.data.name = name;
    first.data.movies = movies;

    QByteArray buff;
    {
        QDataStream out(&buff, QIODevice::WriteOnly);
        first.writeStream(out);
    }

    NetworkData::Theater second;
    QVERIFY(second.data.id != id);
    QVERIFY(second.data.name != name);
    QVERIFY(second.data.movies != movies);

    {
        QDataStream in(&buff, QIODevice::ReadOnly);
        QVERIFY(NetworkData::INetworkDataSctructure::DataType::Theater == NetworkData::INetworkDataSctructure::getDataType(in));
        second.readStream(in);
    }

    QVERIFY(second.data.id == id);
    QVERIFY(second.data.name == name);
    QVERIFY(second.data.movies == movies);
}

void NetworkStructures_Test::testTicketsStruct()
{
    static const quint32 theaterId = 1;
    static const quint32 movieId = 2;
    static const quint32 rowCount = 3;
    static const quint32 colCount = 4;
    static const QVector<Data::Tickets::Status> ticketsStatus = { Data::Tickets::Status::Free, Data::Tickets::Status::Booked, Data::Tickets::Status::TryBook };

    NetworkData::Tickets first;
    first.data.theaterId = theaterId;
    first.data.movieId = movieId;
    first.data.rowCount = rowCount;
    first.data.colCount = colCount;
    first.data.ticketsStatus = ticketsStatus;

    QByteArray buff;
    {
        QDataStream out(&buff, QIODevice::WriteOnly);
        first.writeStream(out);
    }

    NetworkData::Tickets second;
    QVERIFY(second.data.theaterId != theaterId);
    QVERIFY(second.data.movieId != movieId);
    QVERIFY(second.data.rowCount != rowCount);
    QVERIFY(second.data.colCount != colCount);
    QVERIFY(second.data.ticketsStatus != ticketsStatus);

    {
        QDataStream in(&buff, QIODevice::ReadOnly);
        QVERIFY(NetworkData::INetworkDataSctructure::DataType::Tickets == NetworkData::INetworkDataSctructure::getDataType(in));
        second.readStream(in);
    }

    QVERIFY(second.data.theaterId == theaterId);
    QVERIFY(second.data.movieId == movieId);
    QVERIFY(second.data.rowCount == rowCount);
    QVERIFY(second.data.colCount == colCount);
    QVERIFY(second.data.ticketsStatus == ticketsStatus);
}

void NetworkStructures_Test::testBookingResultStruct()
{
    static const bool result = true;

    NetworkData::BookingResult first;
    first.result = result;

    QByteArray buff;
    {
        QDataStream out(&buff, QIODevice::WriteOnly);
        first.writeStream(out);
    }

    NetworkData::BookingResult second;
    QVERIFY(second.result != result);

    {
        QDataStream in(&buff, QIODevice::ReadOnly);
        QVERIFY(NetworkData::INetworkDataSctructure::DataType::BookingResult == NetworkData::INetworkDataSctructure::getDataType(in));
        second.readStream(in);
    }

    QVERIFY(second.result == result);
}

void NetworkStructures_Test::testReuqestTheatersStruct()
{
    NetworkData::ReuqestTheaters first;

    QByteArray buff;
    {
        QDataStream out(&buff, QIODevice::WriteOnly);
        first.writeStream(out);
    }

    NetworkData::ReuqestTheaters second;

    {
        QDataStream in(&buff, QIODevice::ReadOnly);
        QVERIFY(NetworkData::INetworkDataSctructure::DataType::ReuqestTheaters == NetworkData::INetworkDataSctructure::getDataType(in));
        second.readStream(in);
    }
}

void NetworkStructures_Test::testReuqestMoviesStruct()
{
    NetworkData::ReuqestMovies first;

    QByteArray buff;
    {
        QDataStream out(&buff, QIODevice::WriteOnly);
        first.writeStream(out);
    }

    NetworkData::ReuqestMovies second;

    {
        QDataStream in(&buff, QIODevice::ReadOnly);
        QVERIFY(NetworkData::INetworkDataSctructure::DataType::ReuqestMovies == NetworkData::INetworkDataSctructure::getDataType(in));
        second.readStream(in);
    }
}

void NetworkStructures_Test::testReuqestTicketsStruct()
{

    static const quint32 theaterId = 1;
    static const quint32 movieId = 2;

    NetworkData::ReuqestTickets first;
    first.theaterId = theaterId;
    first.movieId = movieId;

    QByteArray buff;
    {
        QDataStream out(&buff, QIODevice::WriteOnly);
        first.writeStream(out);
    }

    NetworkData::ReuqestTickets second;
    QVERIFY(second.theaterId != theaterId);
    QVERIFY(second.movieId != movieId);

    {
        QDataStream in(&buff, QIODevice::ReadOnly);
        QVERIFY(NetworkData::INetworkDataSctructure::DataType::ReuqestTickets == NetworkData::INetworkDataSctructure::getDataType(in));
        second.readStream(in);
    }

    QVERIFY(second.theaterId == theaterId);
    QVERIFY(second.movieId == movieId);
}

void NetworkStructures_Test::testReuqestBookingStruct()
{
    static const quint32 theaterId = 1;
    static const quint32 movieId = 2;
    static const quint32 rowCount = 3;
    static const quint32 colCount = 4;
    static const QVector<Data::Tickets::Status> ticketsStatus = { Data::Tickets::Status::Free, Data::Tickets::Status::Booked, Data::Tickets::Status::TryBook };

    NetworkData::ReuqestBooking first;
    first.data.theaterId = theaterId;
    first.data.movieId = movieId;
    first.data.rowCount = rowCount;
    first.data.colCount = colCount;
    first.data.ticketsStatus = ticketsStatus;

    QByteArray buff;
    {
        QDataStream out(&buff, QIODevice::WriteOnly);
        first.writeStream(out);
    }

    NetworkData::ReuqestBooking second;
    QVERIFY(second.data.theaterId != theaterId);
    QVERIFY(second.data.movieId != movieId);
    QVERIFY(second.data.rowCount != rowCount);
    QVERIFY(second.data.colCount != colCount);
    QVERIFY(second.data.ticketsStatus != ticketsStatus);

    {
        QDataStream in(&buff, QIODevice::ReadOnly);
        QVERIFY(NetworkData::INetworkDataSctructure::DataType::ReuqestBooking == NetworkData::INetworkDataSctructure::getDataType(in));
        second.readStream(in);
    }

    QVERIFY(second.data.theaterId == theaterId);
    QVERIFY(second.data.movieId == movieId);
    QVERIFY(second.data.rowCount == rowCount);
    QVERIFY(second.data.colCount == colCount);
    QVERIFY(second.data.ticketsStatus == ticketsStatus);
}

void NetworkStructures_Test::testDataPackStruct()
{
    static const qsizetype dataSize = 10;

    NetworkData::DataPack first;
    first.dataSize = dataSize;

    QByteArray buff;
    {
        QDataStream out(&buff, QIODevice::WriteOnly);
        first.writeStream(out);
    }

    NetworkData::DataPack second;
    QVERIFY(second.dataSize != dataSize);

    {
        QDataStream in(&buff, QIODevice::ReadOnly);
        QVERIFY(NetworkData::INetworkDataSctructure::DataType::DataPack == NetworkData::INetworkDataSctructure::getDataType(in));
        second.readStream(in);
    }

    QVERIFY(second.dataSize == dataSize);
}

}
