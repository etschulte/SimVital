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
            onClicked: sessionManager.login(usernameInput.text, passwordInput.text)
        }
    }
}