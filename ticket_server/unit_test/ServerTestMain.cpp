#include <QTest>

#include "Connection_Test.h"
#include "TicketsDatabase_Test.h"

namespace Test {
bool serverTest()
{
    bool result = 0;
    {
        Test::TicketsDatabase_Test tdb;
        result |= QTest::qExec(&tdb);
    }
    // problem with QSignalSpy
    // {
    //     Test::Connection_Test ct;
    //     result |= QTest::qExec(&ct);
    // }

    return result;
}
}
