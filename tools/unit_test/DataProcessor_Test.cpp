#include <QSignalSpy>

#include "../DataProcessor.h"
#include "../NetworkStructures.h"

#include "DataProcessor_Test.h"

#include <functional>

namespace Test {
class DataProcessorTestImpl : public DataProcessor {

public:
    DataProcessorTestImpl(DataProcessor_Test* testClass)
        : m_testClass(testClass) {

        };
    virtual ~DataProcessorTestImpl() = default;

public:
    bool parseTextMessage(const QByteArray& msg)
    {
        return parseMessage(msg);
    }

    std::function<void(const Data::Movie&)> cbMovieRecived;
    std::function<void(const Data::Theater&)> cbTheaterRecived;
    std::function<void(const Data::Tickets&)> cbTicketsRecived;
    std::function<void()> cbReuqestMoviesRecived;
    std::function<void()> cbReuqestTheatersRecived;
    std::function<void(quint32, quint32)> cbReuqestTicketsRecived;
    std::function<void(const Data::Tickets&)> cbReuqestBookingRecived;
    std::function<void(bool)> cbBookingResultRecived;
    std::function<void(const QList<Data::Movie>&)> cbMoviePackRecived;
    std::function<void(const QList<Data::Theater>&)> cbTheaterPackRecived;

    bool packMovies(const QList<Data::Movie>& p, QByteArray& buff)
    {
        return packListToMessage<NetworkData::Movie>(p, buff);
    }

    bool packTheaters(const QList<Data::Theater>& p, QByteArray& buff)
    {
        return packListToMessage<NetworkData::Theater>(p, buff);
    }

protected:
    void onMovieRecived(const Data::Movie& m) override { cbMovieRecived(m); };
    void onTheaterRecived(const Data::Theater& t) override { cbTheaterRecived(t); }
    void onTicketsRecived(const Data::Tickets& t) override { cbTicketsRecived(t); };
    void onReuqestMoviesRecived() override { cbReuqestMoviesRecived(); }
    void onReuqestTheatersRecived() override { cbReuqestTheatersRecived(); }
    void onReuqestTicketsRecived(quint32 theaterId, quint32 movieId) override { cbReuqestTicketsRecived(theaterId, movieId); };
    void onReuqestBookingRecived(const Data::Tickets& b) override { cbReuqestBookingRecived(b); }
    void onBookingResultRecived(bool r) override { cbBookingResultRecived(r); }
    void onMoviePackRecived(const QList<Data::Movie>& p) override { cbMoviePackRecived(p); }
    void onTheaterPackRecived(const QList<Data::Theater>& p) override { cbTheaterPackRecived(p); };

private:
    DataProcessor_Test* m_testClass;
};

bool sendStructure(DataProcessorTestImpl* processor, const NetworkData::INetworkDataSctructure& data, NetworkData::INetworkDataSctructure::DataType type)
{
    QByteArray buff;
    QDataStream stream(&buff, QIODevice::WriteOnly);
    data.writeStream(stream, type);
    return processor->parseTextMessage(buff);
}

void DataProcessor_Test::initTestCase()
{
    m_processor.reset(new DataProcessorTestImpl { this });
}

void DataProcessor_Test::testMovieRecived()
{
    bool recived = false;
    m_processor->cbMovieRecived = [&recived](const Data::Movie&) {
        // we don't need to check content,  only  fact of receive
        recived = true;
    };
    QVERIFY(sendStructure(m_processor.get(), NetworkData::Movie {}, NetworkData::INetworkDataSctructure::DataType::Movie));
    QVERIFY(recived);
}

void DataProcessor_Test::testTheaterRecived()
{
    bool recived = false;
    m_processor->cbTheaterRecived = [&recived](const Data::Theater&) {
        // we don't need to check content,  only  fact of receive
        recived = true;
    };
    QVERIFY(sendStructure(m_processor.get(), NetworkData::Theater {}, NetworkData::INetworkDataSctructure::DataType::Theater));
    QVERIFY(recived);
}

void DataProcessor_Test::testTicketsRecived()
{
    bool recived = false;
    m_processor->cbTicketsRecived = [&recived](const Data::Tickets&) {
        // we don't need to check content,  only  fact of receive
        recived = true;
    };
    QVERIFY(sendStructure(m_processor.get(), NetworkData::Tickets {}, NetworkData::INetworkDataSctructure::DataType::Tickets));
    QVERIFY(recived);
}

void DataProcessor_Test::testReuqestMoviesRecived()
{
    bool recived = false;
    m_processor->cbReuqestMoviesRecived = [&recived]() {
        // we don't need to check content,  only  fact of receive
        recived = true;
    };

    QVERIFY(sendStructure(m_processor.get(), NetworkData::ReuqestMovies {}, NetworkData::INetworkDataSctructure::DataType::ReuqestMovies));
    QVERIFY(recived);
}

void DataProcessor_Test::testReuqestTheatersRecived()
{
    bool recived = false;
    m_processor->cbReuqestTheatersRecived = [&recived]() {
        // we don't need to check content,  only  fact of receive
        recived = true;
    };

    QVERIFY(sendStructure(m_processor.get(), NetworkData::ReuqestTheaters {}, NetworkData::INetworkDataSctructure::DataType::ReuqestTheaters));
    QVERIFY(recived);
}

void DataProcessor_Test::testReuqestTicketsRecived()
{
    bool recived = false;
    m_processor->cbReuqestTicketsRecived = [&recived](quint32, quint32) {
        // we don't need to check content,  only  fact of receive
        recived = true;
    };

    QVERIFY(sendStructure(m_processor.get(), NetworkData::ReuqestTickets {}, NetworkData::INetworkDataSctructure::DataType::ReuqestTickets));
    QVERIFY(recived);
}

void DataProcessor_Test::testReuqestBookingRecived()
{
    bool recived = false;
    m_processor->cbReuqestBookingRecived = [&recived](const Data::Tickets&) {
        // we don't need to check content,  only  fact of receive
        recived = true;
    };

    QVERIFY(sendStructure(m_processor.get(), NetworkData::ReuqestBooking {}, NetworkData::INetworkDataSctructure::DataType::ReuqestBooking));
    QVERIFY(recived);
}

void DataProcessor_Test::testBookingResultRecived()
{
    bool recived = false;
    m_processor->cbBookingResultRecived = [&recived](bool) {
        // we don't need to check content,  only  fact of receive
        recived = true;
    };

    QVERIFY(sendStructure(m_processor.get(), NetworkData::BookingResult {}, NetworkData::INetworkDataSctructure::DataType::BookingResult));
    QVERIFY(recived);
}

void DataProcessor_Test::testMoviePackRecived()
{
    QByteArray buff;
    QDataStream stream(&buff, QIODevice::WriteOnly);

    QList<Data::Movie> list;

    for (int i = 0; i < 10; ++i) {
        Data::Movie movie;
        movie.id = i;
        list.push_back(movie);
    }

    m_processor->cbMoviePackRecived = [&list](const QList<Data::Movie>& p) {
        // we don't need to check content,  only  fact of receive
        QVERIFY(list.size() == p.size());
    };

    m_processor->packMovies(list, buff);
}

void DataProcessor_Test::testTheaterPackRecived()
{
    QByteArray buff;
    QDataStream stream(&buff, QIODevice::WriteOnly);

    QList<Data::Theater> list;

    for (int i = 0; i < 10; ++i) {
        Data::Theater movie;
        movie.id = i;
        list.push_back(movie);
    }

    m_processor->cbMoviePackRecived = [&list](const QList<Data::Movie>& p) {
        // we don't need to check content,  only  fact of receive
        QVERIFY(list.size() == p.size());
    };

    m_processor->packTheaters(list, buff);
}
} // namespace Test
