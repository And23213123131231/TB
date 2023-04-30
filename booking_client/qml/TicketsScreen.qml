import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15

import TicketTemplates 1.0
import TicketBooking 1.0

import App 1.0

BasicScreen {
    id: root

    property int theaterId
    property int movieId

    onTheaterIdChanged: {
        TicketsModelController.theaterId = theaterId
    }
    onMovieIdChanged: {
        TicketsModelController.movieId = movieId
    }

    Component.onDestruction: {
        // prevent data storing between sessions
        TicketsModelController.theaterId = 0
        TicketsModelController.movieId = 0
    }

    sourceComponent: ColumnLayout {
        anchors.fill: parent

        GridLayout {
            id: grid
            columns: TicketsModelController.ticketsColumnsCount
            rows: TicketsModelController.ticketsRowsCount

            rowSpacing: 5
            columnSpacing: 5
            anchors.margins: 5

            Repeater {
                model: TicketsModelController
                BasicButton {
                    Layout.row: index / TicketsModelController.ticketsColumnsCount
                    Layout.column: index % TicketsModelController.ticketsColumnsCount
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    textLabel.font.pointSize: Settings.ticketTextSize

                    color: getColor(model.seatStatus)

                    function getColor(seatStatus)
                    {
                        if(TicketsModelController.Free === seatStatus){
                            return Settings.ticketSeatFreeColor
                        }
                        else if(TicketsModelController.TryBook === seatStatus){
                            return Settings.ticketSeatTryBookColor
                        } else if (TicketsModelController.BookedByUser === seatStatus)
                        {
                            return Settings.ticketSeatuserBookedColor
                        }
                        return Settings.ticketSeatBookedColor
                    }

                    text: model.seatName

                    onClicked: {
                        TicketsModelController.tryBook(index)
                    }

                    Text {
                        visible: TicketsModelController.BookedByUser === model.seatStatus
                        anchors.bottom: parent.bottom
                        text: "Booked by you"
                    }
                }
            }
        }
        BasicButton {
            Layout.fillWidth: true
            text: "Confirm booking"
            textLabel.font.pixelSize: Settings.movieDelegateHeaderTextSize

            enabled: TicketsModelController.hasSelection
            onClicked: {
                TicketsModelController.confirmBooking()
            }
        }
    }
}
