#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "BookingClient.h"

namespace {
const int server_port = 7654;
}

int main(int argc, char* argv[])
{
    QGuiApplication app(argc, argv);

    BookingClient client(QUrl(QString("wss://localhost:%1").arg(server_port)));

    return app.exec();
}
