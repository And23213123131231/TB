import QtQuick 2.15

import App 1.0

Rectangle {
    id: root

    property alias text: textLabel.text
    property alias textLabel: textLabel

    signal clicked()

    height: Settings.buttonHeight

    color: enabled ? Settings.enabledButtonColor : Settings.disabledButtonColor

    Text {
        id: textLabel
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.verticalCenter: parent.verticalCenter
        verticalAlignment: Text.Center
        horizontalAlignment: Text.Center
        elide: Text.ElideMiddle
    }

    MouseArea {
        anchors.fill: parent
        cursorShape: Qt.PointingHandCursor

        onClicked: {
            if(root.enabled)
                root.clicked()
        }
    }
}
