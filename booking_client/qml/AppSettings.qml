pragma Singleton

import QtQuick 2.15

QtObject {
    readonly property color backgroudColor: "#FFF"
    readonly property color navigationBarColor: "#59F"
    readonly property color waitModeBlurColor: "#AAAAAAAA"

    readonly property color enabledButtonColor: "#9AF"
    readonly property color disabledButtonColor: "#999"

    readonly property color ticketSeatFreeColor: "#0A3"
    readonly property color ticketSeatBookedColor: "#A03"
    readonly property color ticketSeatTryBookColor: "#AA3"
    readonly property color ticketSeatuserBookedColor: "#FFD700"

    readonly property int navigationBarHeight: 50
    readonly property int buttonHeight: 40
    readonly property int scrollBarWidth: 10

    readonly property int backButtonTextSize: 16

    readonly property int movieDelegateHeaderTextSize: 18

    readonly property int ticketTextSize: 20

}
