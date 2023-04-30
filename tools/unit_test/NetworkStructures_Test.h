#pragma once

#include <QTest>

namespace Test {
class NetworkStructures_Test : public QObject {
    Q_OBJECT

public:
    NetworkStructures_Test() = default;
    ~NetworkStructures_Test() override = default;

private slots:
    void testMovieStruct();
    void testTheaterStruct();
    void testTicketsStruct();
    void testBookingResultStruct();
    void testReuqestTheatersStruct();
    void testReuqestMoviesStruct();
    void testReuqestTicketsStruct();
    void testReuqestBookingStruct();
    void testDataPackStruct();
};
}
