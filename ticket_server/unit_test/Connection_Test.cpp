#include <QSignalSpy>

#include "../network/Connection.h"

#include "Connection_Test.h"

namespace Test {
class DataProcessorTestImpl : public Connection {

public:
    DataProcessorTestImpl() = default;
    virtual ~DataProcessorTestImpl() = default;

public:
    bool parseTextMessage(const QByteArray& msg)
    {
        return parseMessage(msg);
    }

    bool packMovies(const QList<Data::Movie>& p, QByteArray& buff)
    {
        return packListToMessage<NetworkData::Movie>(p, buff);
    }

    bool packTheaters(const QList<Data::Theater>& p, QByteArray& buff)
    {
        return packListToMessage<NetworkData::Theater>(p, buff);
    }

    bool sendStructure(const NetworkData::INetworkDataSctructure& data, NetworkData::INetworkDataSctructure::DataType type)
    {
        QByteArray buff;
        QDataStream stream(&buff, QIODevice::WriteOnly);
        data.writeStream(stream, type);
        return parseTextMessage(buff);
    }

private:
    Connection_Test* m_testClass;
};

void Connection_Test::initTestCase()
{
    m_processor.reset(new DataProcessorTestImpl {});
}

bool verifySignal(QSignalSpy& spy, int expectedCount)
{
    return spy.count() == expectedCount || spy.wait(1000);
}

bool verifyNoSignal(QSignalSpy& spy, int expectedCount)
{
    return spy.count() == expectedCount && !spy.wait(1000);
}

void Connection_Test::testReuqestMoviesRecived()
{
    QSignalSpy spy(m_processor.get(), &DataProcessorTestImpl::bookingRecived);
    QVERIFY(m_processor->sendStructure(NetworkData::ReuqestMovies {}, NetworkData::INetworkDataSctructure::DataType::ReuqestMovies));
    QVERIFY(verifySignal(spy, 1));
    //    QVERIFY(recived);
}

void Connection_Test::testReuqestTheatersRecived()
{
    QVERIFY(m_processor->sendStructure(NetworkData::ReuqestTheaters {}, NetworkData::INetworkDataSctructure::DataType::ReuqestTheaters));
    //    QVERIFY(recived);
}

void Connection_Test::testReuqestTicketsRecived()
{
    QVERIFY(m_processor->sendStructure(NetworkData::ReuqestTickets {}, NetworkData::INetworkDataSctructure::DataType::ReuqestTickets));
    //    QVERIFY(recived);
}

void Connection_Test::testReuqestBookingRecived()
{
    QVERIFY(m_processor->sendStructure(NetworkData::ReuqestBooking {}, NetworkData::INetworkDataSctructure::DataType::ReuqestBooking));
    //    QVERIFY(recived);
}
} // namespace Test
