#pragma once

#include <QTest>

namespace Data {
class Movie;
class Theater;
class Tickets;
}

namespace NetworkData {
class INetworkDataSctructure;
}

namespace Test {
class DataProcessorTestImpl;

class DataProcessor_Test : public QObject {
    Q_OBJECT

public:
    DataProcessor_Test() = default;
    ~DataProcessor_Test() override = default;

private slots:
    void initTestCase();
    void testMovieRecived();
    void testTheaterRecived();
    void testTicketsRecived();
    void testReuqestMoviesRecived();
    void testReuqestTheatersRecived();
    void testReuqestTicketsRecived();
    void testReuqestBookingRecived();
    void testBookingResultRecived();
    void testMoviePackRecived();
    void testTheaterPackRecived();

signals:
    void movieRecived(const Data::Movie&);
    void theaterRecived(const Data::Theater&);
    void ticketsRecived(const Data::Tickets&);
    void reuqestMoviesRecived();
    void reuqestTheatersRecived();
    void reuqestTicketsRecived(int theaterId, int movieId);
    void reuqestBookingRecived(const Data::Tickets&);
    void bookingResultRecived(bool);
    void moviePackRecived(const QList<Data::Movie>&);
    void theaterPackRecived(const QList<Data::Theater>&);

private:
    QSharedPointer<DataProcessorTestImpl> m_processor;
};
}
