#include <QCoreApplication>

#include "TicketServer.h"

int main(int argc, char* argv[])
{
    QCoreApplication app { argc, argv };

    qint16 server_port = 7654;
    {
        bool nextIsPort = false;
        for (const auto& argument : QCoreApplication::arguments()) {
            if (QStringLiteral("--port") == argument) {
                nextIsPort = true;
            } else if (nextIsPort) {
                nextIsPort = false;
                bool isOk = true;
                server_port = argument.toUShort(&isOk);
                if (!isOk) {
                    qCritical() << "Port error, please pass: --port number";
                    exit(0);
                }
            }
        }
    }

    TicketServer server { server_port };
    if (!server.init()) {
        qCritical() << "Server start failed";
        exit(-1);
    }

    return app.exec();
}
