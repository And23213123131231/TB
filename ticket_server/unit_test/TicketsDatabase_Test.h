#pragma once

#include <QTest>

class TicketsDatabase;

namespace Test {
class TicketsDatabase_Test : public QObject {
    Q_OBJECT
public:
    TicketsDatabase_Test() = default;
    ~TicketsDatabase_Test() override = default;

private slots:
    void initTestCase();
    void testInitDatabase();
    void testTicketBooking();

private:
    QSharedPointer<TicketsDatabase> m_database;
};
}
