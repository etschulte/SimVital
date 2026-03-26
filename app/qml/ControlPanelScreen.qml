import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle {
    id: panelRoot
    color: "#1e1e1e"

    property string currentScenario: "Scenario 1"

    Text {
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        text: "Instructor Control Panel"
        color: "#FFFFFF"
    }

    Rectangle {
        width: 800
        height: 50
        anchors.margins: 15
        anchors.horizontalCenter: parent.horizontalCenter
        color: "#2a2a2a"
        radius: 8

        Text {
            anchors.top: parent.top
            anchors.centerIn: parent
            text: "Instructor Control Panel"
            color: "#FFFFFF"
            font.pixelSize: 36
        }
    }

    Rectangle {
        width: 560
        height: 500
        anchors.centerIn: parent
        color: "#2a2a2a"
        radius: 8

        Column {
            anchors.fill: parent
            anchors.margins: 15
            spacing: 15

            Text {
                text: "Scenarios"
                color: "#FFFFFF"
                anchors.horizontalCenter: parent.horizontalCenter
                font.pixelSize: 28
            }

            ScenarioButton {
                scenarioName: "Normal Sinus Rhythm"
                isActive: panelRoot.currentScenario === scenarioName
                onClicked: panelRoot.currentScenario = scenarioName
                textColor: "#a0a0a0"
            }

            ScenarioButton {
                scenarioName: "Scenario 2"
                isActive: panelRoot.currentScenario === scenarioName
                onClicked: panelRoot.currentScenario = scenarioName
                textColor: "#a0a0a0"
            }

            ScenarioButton {
                scenarioName: "Scenario 3"
                isActive: panelRoot.currentScenario === scenarioName
                onClicked: panelRoot.currentScenario = scenarioName
                textColor: "#a0a0a0"
            }
        }
    }
}


