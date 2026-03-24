import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Window {
    width: 800
    height: 480
    visible: true
    title: "SimVital - Patient Monitor"
    color: "#1e1e1e"

    RowLayout {
        anchors.fill: parent

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
            onLogoutScreenRequested: mainLoader.source = "qml/LogoutScreen.qml"
            onTrendsScreenRequested: mainLoader.source = "qml/TrendsScreen.qml"
            onPatientScreenRequested: mainLoader.source = "qml/PatientScreen.qml"
        }
    }    
}