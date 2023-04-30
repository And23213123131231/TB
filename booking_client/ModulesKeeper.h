#pragma once

#include <QSharedPointer>

QT_FORWARD_DECLARE_CLASS(QUrl)

class StackViewController;
class MoviesModelController;
class TheatersModelController;
class TicketsModelController;

/*!
 * \brief The ModulesKeeper class
 * This class is responsible for the correct order of creation and operation of rvc singletons.
 */
class ModulesKeeper {
    friend class StackViewController;

protected:
    /*!
     * \brief ModulesKeeper
     */
    ModulesKeeper();
    /*!
     * \brief registerQmlObjects register all QML/c++ objects
     * qmlSingletones Singletone Url + QML singletone name
     */
    void registerQmlObjects(QList<std::tuple<const QUrl&, const QString>> qmlSingletones);

    QSharedPointer<StackViewController> m_stackController;
    QSharedPointer<MoviesModelController> m_moviesModelController;
    QSharedPointer<TheatersModelController> m_theatersModelController;
    QSharedPointer<TicketsModelController> m_ticketsModelController;

private:
    const char* m_moduleName = "TicketBooking";
};
