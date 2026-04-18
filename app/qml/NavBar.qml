import QtQuick
import QtQuick.Layouts

Rectangle {
    height: 80 // Increased slightly to give the 70px buttons room to breathe
    color: "#2a2a2a"
    radius: 8

    property string activeTab: "Monitor"

    signal monitorScreenRequested()
    signal controlPanelRequested()
    signal logoutScreenRequested()
    signal adminScreenRequested()

    Row {
        anchors.centerIn: parent
        spacing: 40 

        NavButton {
            id: adminButton
            titleText: "Admin"
            iconSource: "qrc:/data/icons/admin.png"
            visible: sessionManager.currentUserRole === "Admin"
            isActive: activeTab === "Admin"
            onClicked: {
                audioManager.setAdminMute(true)
                adminScreenRequested()
                activeTab = "Admin"
            }
        }

        NavButton {
            titleText: "Monitor"
            iconSource: "qrc:/data/icons/monitor.png"
            isActive: activeTab === "Monitor"
            onClicked: {
                monitorScreenRequested()
                audioManager.setAdminMute(false)
                activeTab = "Monitor"
            }
        }

        NavButton {
            titleText: "Silence"
            iconSource: "qrc:/data/icons/silence.png"
            onClicked: {
                audioManager.silenceAlarms()
            }
        } 

        NavButton {
            titleText: "Reset"
            iconSource: "qrc:/data/icons/reset.png"
            onClicked: {
                simEngine.switchScenario("data/jsonFiles/normal.json")
            }
        } 

        NavButton {
            titleText: "Control Panel"
            iconSource: "qrc:/data/icons/control-panel.png"
            isActive: activeTab === "ControlPanel"
            onClicked: {
                controlPanelRequested()
                audioManager.setAdminMute(false)
                activeTab = "ControlPanel"
            }
        } 

        NavButton {
            titleText: "Logout"
            iconSource: "qrc:/data/icons/logout.png"
            onClicked: {
                logoutScreenRequested()
            }
        } 
    }
}