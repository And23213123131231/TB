import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15

import TicketBooking 1.0

ApplicationWindow {
    minimumWidth: 640
    minimumHeight: 320
    height: 1024
    visible: true

    StackView {
        id: view

        anchors.fill: parent
    }

    Connections {
        target: StackViewController

        function onOpenScreen(url, properties) {
            view.push(url, properties)

        }
        function onCloseScreen() {
            view.pop()
        }
    }

    Component.onCompleted: StackViewController.guiStarted()
}
