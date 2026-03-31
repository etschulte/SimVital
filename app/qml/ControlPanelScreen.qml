import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle {
    id: panelRoot
    color: "#1e1e1e"

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
                isActive: simEngine ? simEngine.currentScenario === scenarioName : false
                onClicked: {
                    simEngine.switchScenario("data/jsonFiles/normal.json")
                    console.log("switched to normal")
                }
                textColor: "#a0a0a0"
            }

            ScenarioButton {
                scenarioName: "Ventricular Tachycardia"
                isActive: simEngine ? simEngine.currentScenario === scenarioName : false
                onClicked: {
                    simEngine.switchScenario("data/jsonFiles/vtach.json")
                    console.log("switched to vtach")
                }
                textColor: "#a0a0a0"
            }

            ScenarioButton {
                scenarioName: "Atrial Fibrillation"
                isActive: simEngine ? simEngine.currentScenario === scenarioName : false
                onClicked: {
                    simEngine.switchScenario("data/jsonFiles/afib.json")
                    console.log("switched to afib")
                }
                textColor: "#a0a0a0"
            }

            ScenarioButton {
                scenarioName: "Ventricular Bigeminy"
                isActive: simEngine ? simEngine.currentScenario === scenarioName : false
                onClicked: {
                    simEngine.switchScenario("data/jsonFiles/bigeminy.json")
                    console.log("switched to bigeminy")
                }
                textColor: "#a0a0a0"
            }

            ScenarioButton {
                scenarioName: "Ventricular Fibrillation"
                isActive: simEngine ? simEngine.currentScenario === scenarioName : false
                onClicked: {
                    simEngine.switchScenario("data/jsonFiles/vfib.json")
                    console.log("switched to vfib")
                }
                textColor: "#a0a0a0"
            }
        }
    }
}


