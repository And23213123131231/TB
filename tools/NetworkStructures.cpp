#include "NetworkStructures.h"

// TODO: protocol version should be added

namespace NetworkData {

bool INetworkDataSctructure::transactionReadStream(QDataStream& in, DataType expectedtype, std::function<void(QDataStream&)> readDataCollback)
{
    in.startTransaction();
    DataType type;
    in >> type;
    if (type != expectedtype) {
        in.rollbackTransaction();
        return false;
    }
    readDataCollback(in);
    return in.commitTransaction();
}

bool INetworkDataSctructure::transactionWriteStream(QDataStream& out, DataType expectedtype, std::function<void(QDataStream&)> writeDataCollback) const
{
    out.startTransaction();
    out << expectedtype;
    writeDataCollback(out);
    return out.commitTransaction();
}

bool Movie::readStream(QDataStream& in, DataType type)
{
    return INetworkDataSctructure::transactionReadStream(in, type,
        [this](QDataStream& in) -> void { in >> data.id >> data.score >> data.name >> data.critics >> data.synopsis >> data.starring >> data.directed; });
}

bool Movie::writeStream(QDataStream& out, DataType type) const
{
    return INetworkDataSctructure::transactionWriteStream(out, type,
        [this](QDataStream& out) -> void {
            out << data.id << data.score << data.name << data.critics << data.synopsis << data.starring << data.directed;
        });
}

bool Theater::readStream(QDataStream& in, DataType type)
{
    return INetworkDataSctructure::transactionReadStream(in, type,
        [this](QDataStream& in) -> void { in >> data.id >> data.name >> data.movies; });
}

bool Theater::writeStream(QDataStream& out, DataType type) const
{
    return INetworkDataSctructure::transactionWriteStream(out, type,
        [this](QDataStream& out) -> void {
            out << data.id << data.name << data.movies;
        });
}

INetworkDataSctructure::DataType INetworkDataSctructure::getDataType(QDataStream& in)
{
    in.startTransaction();
    DataType type;
    in >> type;
    in.rollbackTransaction();

    if (type >= DataType::Movie && type < DataType::_Last) {

        return type;
    }
    return DataType::_Last;
}

bool ReuqestTheaters::readStream(QDataStream& in, DataType type)
{
    return INetworkDataSctructure::transactionReadStream(in, type,
        [this](QDataStream&) -> void {});
}

bool ReuqestTheaters::writeStream(QDataStream& out, DataType type) const
{
    return INetworkDataSctructure::transactionWriteStream(out, type,
        [this](QDataStream&) -> void {});
}

bool ReuqestMovies::readStream(QDataStream& in, DataType type)
{
    return INetworkDataSctructure::transactionReadStream(in, type,
        [this](QDataStream&) -> void {});
}

bool ReuqestMovies::writeStream(QDataStream& out, DataType type) const
{
    return INetworkDataSctructure::transactionWriteStream(out, type,
        [this](QDataStream&) -> void {});
}

bool DataPack::readStream(QDataStream& in, DataType type)
{
    return INetworkDataSctructure::transactionReadStream(in, type,
        [this](QDataStream& in) -> void { in >> dataSize; });
}

bool DataPack::writeStream(QDataStream& out, DataType type) const
{
    return INetworkDataSctructure::transactionWriteStream(out, type,
        [this](QDataStream& out) -> void { out << dataSize; });
}

bool ReuqestTickets::readStream(QDataStream& in, DataType type)
{
    return INetworkDataSctructure::transactionReadStream(in, type,
        [this](QDataStream& in) -> void { in >> theaterId >> movieId; });
}

bool ReuqestTickets::writeStream(QDataStream& out, DataType type) const
{
    return INetworkDataSctructure::transactionWriteStream(out, type,
        [this](QDataStream& out) -> void { out << theaterId << movieId; });
}

bool Tickets::readStream(QDataStream& in, DataType type)
{
    return INetworkDataSctructure::transactionReadStream(in, type,
        [this](QDataStream& in) -> void { in >> data.theaterId >> data.movieId >> data.rowCount
                                              >> data.colCount >> data.ticketsStatus; });
}

bool Tickets::writeStream(QDataStream& out, DataType type) const
{
    return INetworkDataSctructure::transactionWriteStream(out, type,
        [this](QDataStream& out) -> void { out << data.theaterId << data.movieId << data.rowCount
                                               << data.colCount << data.ticketsStatus; });
}

bool ReuqestBooking::readStream(QDataStream& in, DataType type)
{
    return INetworkDataSctructure::transactionReadStream(in, type,
        [this, type](QDataStream& in) -> void { Tickets::readStream(in, type); });
}

bool ReuqestBooking::writeStream(QDataStream& out, DataType type) const
{
    return INetworkDataSctructure::transactionWriteStream(out, type,
        [this, type](QDataStream& out) -> void { Tickets::writeStream(out, type); });
}

bool BookingResult::readStream(QDataStream& in, DataType type)
{
    return INetworkDataSctructure::transactionReadStream(in, type,
        [this](QDataStream& in) -> void { in >> result; });
}

bool BookingResult::writeStream(QDataStream& out, DataType type) const
{
    return INetworkDataSctructure::transactionWriteStream(out, type,
        [this](QDataStream& out) -> void { out << result; });
}

}
