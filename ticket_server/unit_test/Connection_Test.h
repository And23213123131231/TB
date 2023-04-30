#pragma once

#include <QTest>

namespace Test {
class DataProcessorTestImpl;

class Connection_Test : public QObject {
    Q_OBJECT

public:
    Connection_Test() = default;
    ~Connection_Test() override = default;

private slots:
    void initTestCase();
    void testReuqestMoviesRecived();
    void testReuqestTheatersRecived();
    void testReuqestTicketsRecived();
    void testReuqestBookingRecived();

private:
    QSharedPointer<DataProcessorTestImpl> m_processor;
};
}
