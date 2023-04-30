import QtQuick 2.15
import QtQuick.Layouts 1.15

import App 1.0
import TicketBooking 1.0

Item {
    id: root

    property alias sourceComponent: componentLoader.sourceComponent

    readonly property alias screenTitle: title.text

    Rectangle {
        id: mainRect
        anchors.top: navigationBar.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        color: Settings.backgroudColor

        Loader {
            id: componentLoader
            anchors.fill: parent
        }
    }

    Rectangle {
        id: navigationBar

        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top

        height: Settings.navigationBarHeight
        color: Settings.navigationBarColor

        BasicButton {
            id: backButton

            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.verticalCenter: parent.verticalCenter
            height: 40
            width: 100
            textLabel.font.pixelSize: Settings.backButtonTextSize
            text: qsTr("Back")

            enabled: !StackViewController.isMainScreen
            onClicked: {
                StackViewController.popScreen()
            }
        }

        Text {
            id: title
            font.pixelSize: Settings.ticketTextSize
            anchors.left: backButton.right
            anchors.right: parent.right
            anchors.leftMargin: 10
            anchors.rightMargin: 10
            anchors.verticalCenter: parent.verticalCenter

            horizontalAlignment: Text.AlignLeft
            elide: Text.ElideMiddle
            text: StackViewController.screenTitle
        }
    }

    Rectangle {
        id: messageRect

        anchors.fill: parent
        color: Settings.waitModeBlurColor

        readonly property bool isTextMessage: StackViewController.message !== ""
        visible: StackViewController.waitMode || isTextMessage

        MouseArea {
            anchors.fill: parent
        }

        Rectangle {
            width: root.width - 50
            height: textMessage.height + okButton.height + 20
            anchors.centerIn: parent
            visible: messageRect.isTextMessage
            color: Settings.backgroudColor

            Text {
                id: textMessage
                text: StackViewController.message
                font.pixelSize: Settings.backButtonTextSize
                width: parent.width - 20
                anchors.top: parent.top
                anchors.topMargin: 10
                anchors.horizontalCenter: parent.horizontalCenter
                wrapMode: Text.WordWrap
            }

            BasicButton {
                id: okButton

                anchors.right: parent.right
                anchors.bottom: parent.bottom
                anchors.margins: 10
                height: 40
                width: 100
                textLabel.font.pixelSize: Settings.backButtonTextSize
                text: qsTr("Ok")

                onClicked: {
                    StackViewController.acceptMessage()
                }
            }
        }
    }
}
