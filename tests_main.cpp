#include <QCoreApplication>

#include "tools/unit_test/ToolsTestMain.h"

int main(int argc, char* argv[])
{
    QCoreApplication app(argc, argv);
    int result = 0;

    result |= Test::toolsTest();

    return result;
}
