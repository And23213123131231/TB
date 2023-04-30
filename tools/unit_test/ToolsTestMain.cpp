#include <QTest>

#include "DataProcessor_Test.h"
#include "DataStructures_Test.h"
#include "NetworkStructures_Test.h"

namespace Test {
bool toolsTest()
{
    bool result = 0;
    {
        Test::DataStructures_Test ds;
        result |= QTest::qExec(&ds);
    }

    {
        Test::NetworkStructures_Test ns;
        result |= QTest::qExec(&ns);
    }

    {
        Test::DataProcessor_Test dp;
        result |= QTest::qExec(&dp);
    }

    return result;
}
}
