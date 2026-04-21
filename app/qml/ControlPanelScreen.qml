import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle {
    id: panelRoot
    anchors.fill: parent 
    color: "#1e1e1e"

    Rectangle {
        width: parent.width * 0.85
        height: parent.height * 0.85
        anchors.centerIn: parent
        color: "#2a2a2a"
        radius: 8

        ColumnLayout {
            anchors.fill: parent
            anchors.margins: 15
            spacing: 10 

            Text {
                text: "Instructor Control Panel"
                color: "#FFFFFF"
                Layout.alignment: Qt.AlignHCenter
                font.pixelSize: 28
                Layout.bottomMargin: 10
            }

            ScenarioButton {
                scenarioName: "Normal Sinus Rhythm"
                Layout.fillWidth: true
                Layout.preferredHeight: 45 
                isActive: simEngine ? simEngine.currentScenario === scenarioName : false
                onClicked: simEngine.switchScenario("data/jsonFiles/normal.json")
                textColor: "#a0a0a0"
            }

            ScenarioButton {
                scenarioName: "Ventricular Tachycardia"
                Layout.fillWidth: true
                Layout.preferredHeight: 45
                isActive: simEngine ? simEngine.currentScenario === scenarioName : false
                onClicked: simEngine.switchScenario("data/jsonFiles/vtach.json")
                textColor: "#a0a0a0"
            }

            ScenarioButton {
                scenarioName: "Atrial Fibrillation"
                Layout.fillWidth: true
                Layout.preferredHeight: 45
                isActive: simEngine ? simEngine.currentScenario === scenarioName : false
                onClicked: simEngine.switchScenario("data/jsonFiles/afib.json")
                textColor: "#a0a0a0"
            }

            ScenarioButton {
                scenarioName: "Ventricular Bigeminy"
                Layout.fillWidth: true
                Layout.preferredHeight: 45
                isActive: simEngine ? simEngine.currentScenario === scenarioName : false
                onClicked: simEngine.switchScenario("data/jsonFiles/bigeminy.json")
                textColor: "#a0a0a0"
            }

            ScenarioButton {
                scenarioName: "Ventricular Fibrillation"
                Layout.fillWidth: true
                Layout.preferredHeight: 45
                isActive: simEngine ? simEngine.currentScenario === scenarioName : false
                onClicked: simEngine.switchScenario("data/jsonFiles/vfib.json")
                textColor: "#a0a0a0"
            }
            
            Item { Layout.fillHeight: true } 
        }
    }
}