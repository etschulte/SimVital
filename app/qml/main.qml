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
            Layout.fillWidth: true
            Layout.fillHeight: true
            source: "qml/MonitorScreen.qml"
        }

        NavBar {

        }
    }    
}