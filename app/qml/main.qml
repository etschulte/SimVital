import QtQuick
import QtQuick.Controls

Window {
    width: 640
    height: 480
    visible: true
    title: "SimVital - Patient Monitor"
    color: "#1e1e1e" // A nice dark mode background for a medical monitor

    Column {
        anchors.centerIn: parent
        spacing: 30

        // 1. The Data Display
        Text {
            anchors.horizontalCenter: parent.horizontalCenter
            color: "#00ff00" // Classic monitor green
            font.pixelSize: 64
            font.bold: true
            
            // THE MAGIC LINE: Property Binding
            text: "ECG: " + ecgController.ecgVal 
        }

        // 2. The Controls
        Row {
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: 20

            Button {
                text: "Start"
                font.pixelSize: 20
                onClicked: ecgController.start() // Calls your Q_INVOKABLE
            }

            Button {
                text: "Stop"
                font.pixelSize: 20
                onClicked: ecgController.stop() // Calls your Q_INVOKABLE
            }
        }
    }
}