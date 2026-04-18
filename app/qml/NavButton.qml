import QtQuick
import Qt5Compat.GraphicalEffects 

Rectangle {
    id: root
    width: 80 
    height: 70
    
    color: isActive ? "#3d3d3d" : (touchArea.pressed ? "#4d4d4d" : "transparent")
    radius: 8

    property string titleText: "TITLE"
    property url iconSource: ""
    property color baseColor: "#a0a0a0"   
    property color activeColor: "#ffffff" 
    property bool isActive: false

    signal clicked()

    property color currentColor: isActive || touchArea.pressed ? activeColor : baseColor

    MouseArea {
        id: touchArea
        anchors.fill: parent
        onClicked: root.clicked()
    }

    Column {
        anchors.centerIn: parent
        spacing: 6 
        Item {
            width: 32 
            height: 32
            anchors.horizontalCenter: parent.horizontalCenter

            Image {
                id: iconImage
                source: root.iconSource
                anchors.fill: parent
                fillMode: Image.PreserveAspectFit
                visible: false 
            }

            ColorOverlay {
                anchors.fill: iconImage
                source: iconImage
                color: root.currentColor
            }
        }

        Text {
            id: titleLabel
            text: root.titleText
            color: root.currentColor 
            font.pixelSize: 12 
            font.bold: root.isActive 
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }
}