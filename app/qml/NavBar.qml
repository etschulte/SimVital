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
    signal adminScreenRequested()

    Column {
        anchors.centerIn: parent
        spacing: 15

        NavButton {
            id: adminButton
            titleText: "Admin"
            visible: sessionManager.currentUserRole === "Admin"
            onClicked: {
                audioManager.setAdminMute(true)
                adminScreenRequested()
            }
        }

        NavButton {
            titleText: "Monitor"
            iconSource: ""
            onClicked: {
                monitorScreenRequested()
                audioManager.setAdminMute(false)
            }
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
            onClicked: {
                controlPanelRequested()
                audioManager.setAdminMute(false)
            }
        } 

        NavButton {
            titleText: "Logout"
            iconSource: ""
            onClicked: logoutScreenRequested()
        } 
    }
}