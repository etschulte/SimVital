import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle {
    id: root
    color: flashState ? "#8b0000" : "#2a2a2a" 
    radius: 8

    property string valueText: "--/--"
    property string lastMeasureTime: "--:--"
    property bool flashState: false
    property bool isAlarming: false
    
    signal measureClicked()

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

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 8
        
        ColumnLayout {
            spacing: 2
            Layout.alignment: Qt.AlignTop | Qt.AlignLeft
            
            Text {
                text: "NIBP"
                color: "#ffffff"
                font.pixelSize: 24
                font.bold: true
            }
            Text {
                text: "mmHg"
                color: "#a0a0a0"
                font.pixelSize: 12
            }
        }

        Text {
            text: root.valueText
            color: "#ffffff"
            font.pixelSize: 48
            font.bold: true
            
            Layout.fillWidth: true
            Layout.fillHeight: true
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            
            fontSizeMode: Text.Fit
            minimumPixelSize: 20
        }
        
        RowLayout {
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignBottom
            
            Button {
                text: "Measure"
                Layout.preferredWidth: 85
                Layout.preferredHeight: 30
                
                
                background: Rectangle {
                    color: parent.down ? "#2a5caa" : "#3b78d8" 
                    radius: 4
                }
                contentItem: Text {
                    text: parent.text
                    color: "white"
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    font.pixelSize: 14
                    font.bold: true
                }
                
                onClicked: root.measureClicked()
            }
            
            Item { Layout.fillWidth: true } 
            
            ColumnLayout {
                spacing: 0
                Layout.alignment: Qt.AlignRight
                
                Text {
                    text: "Last:"
                    color: "#a0a0a0"
                    font.pixelSize: 11
                }
                Text {
                    text: root.lastMeasureTime
                    color: "#a0a0a0"
                    font.pixelSize: 11
                }
            }
        }
    }
}