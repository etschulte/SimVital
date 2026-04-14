import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Window {
    width: 1600
    height: 960
    visible: true
    title: "SimVital - Patient Monitor"
    color: "#1e1e1e"

    RowLayout {
        anchors.fill: parent
        visible: sessionManager ? sessionManager.currentUserRole != "" : false 

        Loader {
            id: mainLoader
            Layout.fillWidth: true
            Layout.fillHeight: true
            source: "qml/MonitorScreen.qml"
        }

        NavBar {
            Layout.preferredWidth: 80
            Layout.fillHeight: true
            Layout.topMargin: 60
            Layout.bottomMargin: 15
            Layout.rightMargin: 15

            onMonitorScreenRequested: mainLoader.source = "qml/MonitorScreen.qml"
            onControlPanelRequested: mainLoader.source = "qml/ControlPanelScreen.qml"
            onLogoutScreenRequested: logoutScreen.open()
            onTrendsScreenRequested: mainLoader.source = "qml/TrendsScreen.qml"
            onPatientScreenRequested: mainLoader.source = "qml/PatientScreen.qml"
        }
    }

    LogoutScreen {
        id: logoutScreen
    }

    Loader {
        id: loginLoader
        anchors.fill: parent
        source: "qml/LoginScreen.qml"
        visible: sessionManager ? sessionManager.currentUserRole === "" : false
    }
}