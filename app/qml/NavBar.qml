import QtQuick
import QtQuick.Layouts

Rectangle {
    width: 80
    color: "#2a2a2a"
    radius: 8

    Column {
        anchors.centerIn: parent
        spacing: 15

        NavButton {
            titleText: "Monitor"
            iconSource: ""
        }

        NavButton {
            titleText: "Trends"
            iconSource: ""
        } 

        NavButton {
            titleText: "Patient"
            iconSource: ""
        } 

        NavButton {
            titleText: "Silence"
            iconSource: ""
        } 

        NavButton {
            titleText: "Control Panel"
            iconSource: ""
        } 

        NavButton {
            titleText: "Logout"
            iconSource: ""
        } 
    }
}