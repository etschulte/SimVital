import QtQuick
import QtQuick.Layouts

Rectangle {
    width: 80
    color: "#2a2a2a"
    radius: 8

    signal monitorScreenRequested()
    signal controlPanelRequested()
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
            titleText: "Reset"
            iconSource: ""
            onClicked: simEngine.switchScenario("data/jsonFiles/normal.json")
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