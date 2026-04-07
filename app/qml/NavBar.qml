import QtQuick
import QtQuick.Layouts

Rectangle {
    width: 80
    color: "#2a2a2a"
    radius: 8

    signal monitorScreenRequested()
    signal controlPanelRequested()
    signal trendsScreenRequested()
    signal patientScreenRequested()
    signal logoutScreenRequested()

    Column {
        anchors.centerIn: parent
        spacing: 15

        NavButton {
            titleText: "Monitor"
            iconSource: ""
            onClicked: monitorScreenRequested()
        }

        NavButton {
            titleText: "Trends"
            iconSource: ""
            onClicked: trendsScreenRequested()
        } 

        NavButton {
            titleText: "Patient"
            iconSource: ""
            onClicked: patientScreenRequested()
        } 

        NavButton {
            titleText: "Silence"
            iconSource: ""
            onClicked: audioManager.silenceAlarms()
        } 

        NavButton {
            titleText: "Control Panel"
            iconSource: ""
            onClicked: controlPanelRequested()
        } 

        NavButton {
            titleText: "Logout"
            iconSource: ""
            onClicked: logoutScreenRequested()
        } 
    }
}