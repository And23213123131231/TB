#include "BookingClient.h"

#include <QQmlApplicationEngine>

#include "controllers/MoviesModelController.h"
#include "controllers/StackViewController.h"
#include "controllers/TheatersModelController.h"
#include "controllers/TicketsModelController.h"

#include "network/Client.h"

BookingClient::BookingClient(QUrl&& url, QObject* parent)
    : QObject(parent)
    , ModulesKeeper()
    , m_client(new Client { std::move(url) })
    , m_engine(new QQmlApplicationEngine { this })
{
    // extra style data.
    // TODO: move to style singletone class
    registerQmlObjects({ { QUrl("qrc:/qml/AppSettings.qml"), "Settings" } });

    connect(m_client, &Client::transferStatus, this, [](bool transferInProgress, const QString& reason) {
        StackViewController::get()->setWaitMode(transferInProgress);
        if (!reason.isEmpty()) {
            StackViewController::get()->showMessage(reason);
        }
    });

    connect(m_client, &Client::ticketsRecived, m_ticketsModelController.get(),
        &TicketsModelController::updateModel);

    connect(m_ticketsModelController.get(), &TicketsModelController::requestTickets, this, [this](int theaterId, int movieId) {
        m_client->requestTickets(theaterId, movieId);
    });

    connect(m_ticketsModelController.get(), &TicketsModelController::requestTickets, this, [this](int theaterId, int movieId) {
        m_client->requestTickets(theaterId, movieId);
    });

    connect(m_ticketsModelController.get(), &TicketsModelController::ticketsConfirmationRequest, this, [this](const Data::Tickets& tickets) {
        m_client->bookTickets(tickets);
    });

    connect(m_client, &Client::bookingResult, this, [this](bool result) {
        m_ticketsModelController->confirmationResult(result);
    });

    connect(m_client, &Client::moviePackRecived, m_moviesModelController.get(),
        &MoviesModelController::setModelList);

    connect(m_client, &Client::thaterPackRecived, m_theatersModelController.get(),
        &TheatersModelController::setModelList);

    connect(m_stackController.get(), &StackViewController::onGuiStarted, this,
        [this]() {
            StackViewController::get()->pushScreen("MoviesScreen", QVariantMap(), QStringLiteral("Movies"));
            m_client->connectToServer();
        });

    m_engine->load(QUrl("qrc:/qml/main.qml"));
}

BookingClient::~BookingClient() { }

void BookingClient::applicationStarted() { }
