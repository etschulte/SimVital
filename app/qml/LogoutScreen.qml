import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Popup {
    id: logoutConfirmation
    width: 400
    height: 200
    modal: true
    anchors.centerIn: Overlay.overlay

    ColumnLayout {
        Text {
            text: "Are you sure you want to log out?"
            Layout.preferredWidth: 300
            Layout.preferredHeight: 60
            font.pixelSize: 24
        }

        RowLayout {
            Button {
                id: cancelBtn
                text: "Cancel"
                Layout.preferredWidth: 140
                Layout.preferredHeight: 60
                font.pixelSize: 24
                onClicked: {
                    logoutConfirmation.close()
                    logoutConfirmation.visible = false
                }
            }

            Button {
                id: confirmBtn
                text: "Logout"
                palette.button: "#2a5caa"
                Layout.preferredWidth: 140
                Layout.preferredHeight: 60
                font.pixelSize: 24
                onClicked: {
                    sessionManager.logout()
                    logoutConfirmation.close()
                    logoutConfirmation.visible = false
                }
            }
        }
    }
}