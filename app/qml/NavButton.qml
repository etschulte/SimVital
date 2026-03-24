import QtQuick

Rectangle {
    id: root
    width: 60; height: 70
    color: "transparent"

    property string titleText: "TITLE"
    property url iconSource: ""
    property color textColor: "#a0a0a0" 

    // --- Custom Signal ---
    signal clicked()

    // --- Interaction ---
    MouseArea {
        id: touchArea
        anchors.fill: parent
        
        onClicked: root.clicked()
    }

    // --- Visual Layout ---
    Column {
        anchors.centerIn: parent
        spacing: 4 

        Image {
            source: root.iconSource
            width: 32 
            height: 32
            fillMode: Image.PreserveAspectFit
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Text {
            id: titleLabel
            text: root.titleText
            color: touchArea.pressed ? "#ffffff" : root.textColor 
            font.pixelSize: 10 
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }
}