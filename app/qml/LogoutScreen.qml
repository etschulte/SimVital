import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Popup {
    id: logoutConfirmation
    width: 450
    height: 250
    modal: true
    anchors.centerIn: Overlay.overlay

    background: Rectangle {
        color: "#252525" 
        radius: 12
        border.color: "#3d3d3d"
        border.width: 1
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 30
        spacing: 15

        Text {
            text: "Are you sure you want to log out?"
            color: "white"
            font.pixelSize: 22
            Layout.alignment: Qt.AlignHCenter
            Layout.topMargin: 10
        }

        Rectangle {
            Layout.fillWidth: true
            Layout.preferredHeight: 1
            color: "#444444"
            Layout.topMargin: 10
            Layout.bottomMargin: 10
        }

        RowLayout {
            spacing: 25
            Layout.alignment: Qt.AlignHCenter
            
            Button {
                id: confirmBtn
                text: "Logout"
                Layout.preferredWidth: 140
                Layout.preferredHeight: 50

                contentItem: Text {
                    text: confirmBtn.text
                    font.pixelSize: 20
                    font.bold: true
                    color: "white"
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }

                background: Rectangle {
                    // Darkens slightly when pressed
                    color: confirmBtn.down ? "#1c3f77" : "#2a5caa" 
                    radius: 8
                }

                onClicked: {
                    sessionManager.logout()
                    logoutConfirmation.close()
                }
            }

            Button {
                id: cancelBtn
                text: "Cancel"
                Layout.preferredWidth: 140
                Layout.preferredHeight: 50

                contentItem: Text {
                    text: cancelBtn.text
                    font.pixelSize: 20
                    color: "#aaaaaa"
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }

                background: Rectangle {
                    color: cancelBtn.down ? "#333333" : "transparent"
                    radius: 8
                    border.color: "#555555"
                    border.width: 1
                }

                onClicked: {
                    logoutConfirmation.close()
                }
            }
        }
    }
}