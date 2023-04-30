#pragma once

#include <QObject>

#include "ModulesKeeper.h"

QT_FORWARD_DECLARE_CLASS(QQmlApplicationEngine)

class Client;

/*!
 * \brief The BookingClient class
 * Represent QML Application with QML engine inside
 * It is the root part of client application.
 * An application must have only one class of a given type at a time.
 */
class BookingClient : public QObject, public ModulesKeeper {
    Q_OBJECT

public:
    /*!
     * \brief BookingClient
     * \param url Web socket server url, such as wss://localhost:1234
     * \param parent object parent
     */
    BookingClient(QUrl&& url, QObject* parent = nullptr);
    ~BookingClient() override;

private slots:
    /*!
     * \brief applicationStarted This method will be called after UI will have been appears
     */
    void applicationStarted();

private:
    Client* m_client;
    QQmlApplicationEngine* m_engine;
};
