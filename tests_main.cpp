#include <QTest>

#include "ticket_server/unit_test/ServerTestMain.h"
#include "tools/unit_test/ToolsTestMain.h"

int main(int argc, char* argv[])
{
    QCoreApplication app(argc, argv);
    int result = 0;

    result |= Test::toolsTest();
    result |= Test::serverTest();

    return result;
}
