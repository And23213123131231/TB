#pragma once

#include <QObject>
#include <QStack>
#include <QVariantMap>

/*!
 * \brief The StackViewController class
 * This class represents the navigation mechanism. It controls the creation of windows and their removal.
 * All windows created in the application must be inherited from the BaseScreen.qml for the class to work correctly.
 */
class StackViewController : public QObject {
    Q_OBJECT

    Q_PROPERTY(bool isMainScreen READ isMainScreen NOTIFY screenChanged)
    Q_PROPERTY(bool waitMode READ waitMode NOTIFY waitModeChanged)
    Q_PROPERTY(QString message READ message NOTIFY messageChanged)
    Q_PROPERTY(QString screenTitle READ screenTitle NOTIFY screenChanged)

    struct Screen {
        QString screenQml;
        QString screenTitle;
    };

public:
    /*!
     * \brief StackViewController
     * \param parent parent object
     */
    StackViewController(QObject* parent = nullptr);
    ~StackViewController() override;

    /*!
     * \brief pushScreen
     * \param screenName name of qml object without prefix path and extension
     * \param properties initial properties for the screen
     * \param title Screen title
     */
    Q_INVOKABLE void pushScreen(const QString& screenName, const QVariantMap& properties = QVariantMap {}, const QString& title = "");
    /*!
     * \brief popScreen return to previous screen
     */
    Q_INVOKABLE void popScreen();

    /*!
     * \brief guiStarted
     * This methon is using by QML application.
     * It will be called after application window is appears
     */
    Q_INVOKABLE void guiStarted();

    /*!
     * \brief isMainScreen
     * \return if current screen is root screen
     */
    bool isMainScreen() const
    {
        return 1 >= m_screensStack.size();
    }

    /*!
     * \brief screenTitle Last screen Title
     * \return title
     */
    QString screenTitle()
    {
        if (!m_screensStack.isEmpty()) {
            return m_screensStack.last().screenTitle;
        }
        return QString();
    }

    /*!
     * \brief showMessage show text message  to user
     */
    Q_INVOKABLE void showMessage(const QString&);

    /*!
     * \brief acceptMessage user was notified
     */
    Q_INVOKABLE void acceptMessage();

    /*!
     * \brief get Get singletone object
     * \return instance
     */
    static StackViewController* get();

    /*!
     * \brief waitMode
     * \return return true if waite mode is active
     */
    bool waitMode();

    /*!
     * \brief setWaitMode set wait mode status
     * \param wait
     */
    void setWaitMode(bool wait);

    /*!
     * \brief message message for user notifying
     * \return
     */
    const QString& message() const;

signals:
    /*!
     * \brief openScreen
     * Internal signal for QML StackView. It is opening  new Screen
     */
    void openScreen(const QUrl&, const QVariantMap&);

    /*!
     * \brief closeScreen
     * Internal signal for QML StackView. It is closing  current Screen
     *
     */
    void closeScreen();

    /*!
     * \brief onGuiStarted
     * This signal means the application window is appears
     */
    void onGuiStarted();

    /*!
     * \brief screenChanged
     */
    void screenChanged();

    /*!
     * \brief waitModeChanged
     */
    void waitModeChanged();

    /*!
     * \brief messageChanged
     */
    void messageChanged();

private:
    static StackViewController* s_stack;
    QStack<Screen> m_screensStack;
    QStringList m_sreensTitles;
    bool m_waitMode = false;
    QString m_message;
};
