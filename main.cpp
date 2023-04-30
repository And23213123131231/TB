#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "ticket_server/TicketServer.h"

#include "booking_client/BookingClient.h"

namespace {
const int server_port = 7654;
}

int main(int argc, char* argv[])
{
    QGuiApplication app{argc, argv};

    TicketServer server{server_port};
    if (!server.init()) {
        qCritical() << "Server start failed";
        app.exit(0);
    }

    BookingClient client{QUrl{QString("wss://localhost:%1").arg(server_port)}};

    return app.exec();
}
