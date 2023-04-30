#include <QDebug>
#include <QUrl>

#include "StackViewController.h"

StackViewController* StackViewController::s_stack(nullptr);

StackViewController::StackViewController(QObject* parent)
    : QObject(parent)
{
    s_stack = this;
}

StackViewController::~StackViewController()
{
    s_stack = nullptr;
}

void StackViewController::pushScreen(const QString& screenName, const QVariantMap& properties, const QString& title)
{
    m_screensStack.push(Screen { screenName, title });
    qDebug() << QStringLiteral("Screen pushed: ") << screenName << title;
    emit openScreen(QUrl(QStringLiteral("qrc:/qml/%1.qml").arg(screenName)), properties);
    emit screenChanged();
}

void StackViewController::popScreen()
{
    auto screen = m_screensStack.pop();
    qDebug() << QStringLiteral("Screen poped: ") << screen.screenQml << screen.screenTitle;
    emit closeScreen();
    emit screenChanged();
}

void StackViewController::guiStarted()
{
    emit onGuiStarted();
}

void StackViewController::showMessage(const QString& message)
{
    m_message = message;
    emit messageChanged();
}

void StackViewController::acceptMessage()
{
    showMessage("");
}

StackViewController* StackViewController::get()
{
    return s_stack;
}

bool StackViewController::waitMode()
{
    return m_waitMode;
}

void StackViewController::setWaitMode(bool wait)
{
    if (m_waitMode != wait) {
        m_waitMode = wait;
        emit waitModeChanged();
    }
}

const QString& StackViewController::message() const
{
    return m_message;
}
