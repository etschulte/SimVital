import QtQuick

Rectangle {
    id: root
    width: 200; height: 180
    color: "#2a2a2a"
    radius: 8

    property string titleText: "TITLE"
    property string unitText: "unit"
    property string valueText: "--"
    property color valueColor: "#ffffff"

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