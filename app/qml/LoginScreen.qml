import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle {
    id: panelRoot
    color: "#1e1e1e"
    anchors.fill: parent

    ColumnLayout {
        anchors.centerIn: parent

        TextField {
            id: usernameInput
            Layout.preferredWidth: 300
            Layout.preferredHeight: 60
            font.pixelSize: 24
            placeholderText: "Username"
        }

        TextField {
            id: passwordInput
            Layout.preferredWidth: 300
            Layout.preferredHeight: 60
            font.pixelSize: 24
            placeholderText: "Password"
            echoMode: TextInput.Password
        }

        Button {
            text: "Login"
            Layout.preferredWidth: 300
            Layout.preferredHeight: 60
            font.pixelSize: 24
            onClicked: {
                errorText.visible = false;
                sessionManager.login(usernameInput.text, passwordInput.text)
            }
        }

        Text {
            id: errorText
            text: "Invalid Credentials"
            Layout.preferredWidth: 300
            Layout.preferredHeight: 60
            font.pixelSize: 24
            color: "#8b0000"
            visible: false
        }
    }

    Connections {
        target: sessionManager

        function onLoginFailed() {
            errorText.visible = true;
        }
    }
}