#include <QQmlApplicationEngine>

#include "controllers/MoviesModelController.h"
#include "controllers/StackViewController.h"
#include "controllers/TheatersModelController.h"
#include "controllers/TicketsModelController.h"

#include "ModulesKeeper.h"

ModulesKeeper::ModulesKeeper()
    : m_stackController(new StackViewController {})
    , m_moviesModelController(new MoviesModelController {})
    , m_theatersModelController(new TheatersModelController {})
    , m_ticketsModelController(new TicketsModelController {})
{
}

void ModulesKeeper::registerQmlObjects(QList<std::tuple<const QUrl&, const QString>> qmlSingletones)
{
    qmlRegisterSingletonInstance(m_moduleName, 1, 0, "StackViewController", m_stackController.get());
    qmlRegisterSingletonInstance(m_moduleName, 1, 0, "MoviesModelController", m_moviesModelController.get());
    qmlRegisterSingletonInstance(m_moduleName, 1, 0, "TheatersModelController", m_theatersModelController.get());
    qmlRegisterSingletonInstance(m_moduleName, 1, 0, "TicketsModelController", m_ticketsModelController.get());
    qmlRegisterType<TicketsModelController::TicketStatus>(m_moduleName, 1, 0, "TicketStatus");

    for (const auto& [url, name] : qmlSingletones) {
        qmlRegisterSingletonType(url, "App", 1, 0, name.toUtf8());
    }
}
