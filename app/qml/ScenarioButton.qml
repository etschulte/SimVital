import QtQuick

Rectangle {
    id: root

    property string scenarioName: "SCENARIO NAME"
    property color textColor: "#a0a0a0" 
    property bool isActive: false

    width: 530
    height: 70
    radius: 8
    color: isActive ? "#3E8937" : "#4D4C4C"

    signal clicked()

    MouseArea {
        id: touchArea
        anchors.fill: parent

        onClicked: root.clicked()
    }

    Text {
        id: scenarioLabel
        text: root.scenarioName
        color: "#ffffff"
        font.pixelSize: 20
        anchors.centerIn: parent
    }
}