import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle {
    id: panelRoot
    color: "#1e1e1e" 
    anchors.fill: parent

    Rectangle {
        width: 450
        height: 400
        anchors.centerIn: parent
        color: "#252525"
        radius: 12
        border.color: "#3d3d3d"
        border.width: 1

        ColumnLayout {
            anchors.fill: parent
            anchors.margins: 40
            spacing: 20

            Text {
                text: "SimVital System Access"
                color: "white"
                font.pixelSize: 22
                font.bold: true
                Layout.alignment: Qt.AlignHCenter
                Layout.bottomMargin: 15
            }

            TextField {
                id: usernameInput
                Layout.fillWidth: true
                Layout.preferredHeight: 50
                font.pixelSize: 18
                placeholderText: "Username"
                color: "white"
                
                background: Rectangle {
                    color: "#1e1e1e"
                    border.color: usernameInput.activeFocus ? "#2a5caa" : "#444444"
                    border.width: usernameInput.activeFocus ? 2 : 1
                    radius: 6
                }
            }

            TextField {
                id: passwordInput
                Layout.fillWidth: true
                Layout.preferredHeight: 50
                font.pixelSize: 18
                placeholderText: "Password"
                echoMode: TextInput.Password
                color: "white"
                
                background: Rectangle {
                    color: "#1e1e1e"
                    border.color: passwordInput.activeFocus ? "#2a5caa" : "#444444"
                    border.width: passwordInput.activeFocus ? 2 : 1
                    radius: 6
                }
            }

            Text {
                id: errorText
                text: "Invalid username or password."
                Layout.fillWidth: true
                font.pixelSize: 15
                color: "#ff4444" 
                horizontalAlignment: Text.AlignHCenter
                opacity: 0.0 
                
                Behavior on opacity { NumberAnimation { duration: 200 } }
            }

            Item { Layout.fillHeight: true } 
            Button {
                id: loginBtn
                text: "Login"
                Layout.fillWidth: true
                Layout.preferredHeight: 50

                contentItem: Text {
                    text: loginBtn.text
                    font.pixelSize: 20
                    font.bold: true
                    color: "white"
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }

                background: Rectangle {
                    color: loginBtn.down ? "#1c3f77" : "#2a5caa"
                    radius: 8
                }

                onClicked: {
                    errorText.opacity = 0.0
                    sessionManager.login(usernameInput.text, passwordInput.text)
                }
            }
        }
    }

    Connections {
        target: sessionManager

        function onLoginFailed() {
            errorText.opacity = 1.0
            passwordInput.text = "" 
        }

        function onLoginSuccess() {
            usernameInput.text = ""
            passwordInput.text = ""
            errorText.opacity = 0.0
        }
    }
}