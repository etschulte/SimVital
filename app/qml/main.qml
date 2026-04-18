import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Window {
    width: 1600
    height: 960
    visible: true
    title: "SimVital - Patient Monitor"
    color: "#1e1e1e"

    ColumnLayout {
        anchors.fill: parent
        visible: sessionManager ? sessionManager.currentUserRole != "" : false
        spacing: 0

        Loader {
            id: mainLoader
            Layout.fillWidth: true
            Layout.fillHeight: true
            source: "qml/MonitorScreen.qml"
        }

        NavBar {
            Layout.fillWidth: true
            Layout.preferredHeight: 60
            Layout.leftMargin: 15
            Layout.rightMargin: 15
            Layout.bottomMargin: 15
            onMonitorScreenRequested: mainLoader.source = "qml/MonitorScreen.qml"
            onControlPanelRequested: mainLoader.source = "qml/ControlPanelScreen.qml"
            onLogoutScreenRequested: logoutScreen.open()
            onAdminScreenRequested: mainLoader.source = "qml/AdminScreen.qml"
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