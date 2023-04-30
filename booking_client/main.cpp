#include "BookingClient.h"
#include <QGuiApplication>
#include <QQmlApplicationEngine>

int main(int argc, char* argv[])
{
    QGuiApplication app { argc, argv };

    QString serverUrl = QStringLiteral("wss://localhost:7654");
    {
        bool nextIsServerAddr = false;
        for (const auto& argument : QCoreApplication::arguments()) {
            if (QStringLiteral("--addr") == argument) {
                nextIsServerAddr = true;
            } else if (nextIsServerAddr) {
                nextIsServerAddr = false;
                serverUrl = QStringLiteral("wss://%1").arg(argument);
            }
        }
    }

    BookingClient client(QUrl { serverUrl });

    return app.exec();
}
