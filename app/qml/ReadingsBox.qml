import QtQuick

Rectangle {
    id: root
    width: 200; height: 180
    color: flashState ? "#8b0000" : "#2a2a2a" 
    radius: 8

    property string titleText: "TITLE"
    property string unitText: "unit"
    property string valueText: "--"
    property color valueColor: "#ffffff"
    property bool flashState: false
    property bool isAlarming: false

    Timer {
        id: alarmTimer
        interval: 500      
        repeat: true
        running: root.isAlarming 
        
        onTriggered: {
            root.flashState = !root.flashState
        }
        
        onRunningChanged: {
            if (!running) {
                root.flashState = false
            }
        }
    }

    Text {
        id: titleLabel
        text: root.titleText
        color: "#ffffff"
        font.pixelSize: 24
        font.bold: true

        anchors.top: parent.top
        anchors.left: parent.left
        anchors.margins: 15
    }

    Text {
        id: unitLabel
        text: root.unitText
        color: "#a0a0a0"
        font.pixelSize: 14

        anchors.top: titleLabel.bottom
        anchors.left: titleLabel.left
        anchors.margins: 2
    }

    Text {
        id: valueLabel
        text: root.valueText
        color: root.valueColor
        font.pixelSize: 72
        font.bold: true

        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.margins: 15
    }
}