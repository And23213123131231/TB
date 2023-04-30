
import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15

import TicketTemplates 1.0
import TicketBooking 1.0

import App 1.0

BasicScreen {
    id: root

    property int movieId

    onMovieIdChanged: {
        TheatersModelController.movieId = movieId
    }

    sourceComponent: ListView {
        model: TheatersModelController

        ScrollBar.vertical: ScrollBar {
            width: Settings.scrollBarWidth
        }

        spacing: 30

        delegate: Item {
            height: layout.height
            width: root.width

            Column {
                id: layout
                spacing: 10
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.margins: 10
                topPadding: 10
                bottomPadding: 10

                component WrappedText: Text {
                    wrapMode: Text.WordWrap
                    width: parent.width
                }

                BasicButton {
                    anchors.left: parent.left
                    anchors.right: parent.right
                    text: model.name
                    textLabel.font.pointSize: Settings.movieDelegateHeaderTextSize
                    textLabel.font.bold: true

                    onClicked: {
                        StackViewController.pushScreen("TicketsScreen", {movieId: movieId, theaterId: model.id}, screenTitle + " > " + model.name)
                    }
                }

            }
        }
    }
}
