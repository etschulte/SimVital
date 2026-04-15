import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle {
    id: adminScreenRoot
    anchors.fill: parent
    color: "#1e1e1e" 

    RowLayout {
        anchors.fill: parent
        anchors.margins: 30
        spacing: 40

        // ==========================================
        // LEFT SIDE: The User Roster (ListView)
        // ==========================================
        ColumnLayout {
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.preferredWidth: parent.width * 0.55

            Text {
                text: "System Users"
                color: "white"
                font.pixelSize: 24
                font.bold: true
                Layout.bottomMargin: 10
            }

            ListView {
                id: userList
                Layout.fillWidth: true
                Layout.fillHeight: true
                model: adminManager.userModel
                clip: true
                spacing: 10

                delegate: Rectangle {
                    width: ListView.view.width
                    height: 70
                    color: "#2d2d2d"
                    radius: 8

                    RowLayout {
                        anchors.fill: parent
                        anchors.margins: 15

                        ColumnLayout {
                            Layout.fillWidth: true
                            spacing: 4

                            Text {
                                text: model.firstName + " " + model.lastName
                                color: "white"
                                font.pixelSize: 18
                                font.bold: true
                            }
                            Text {
                                text: "Username: " + model.username + "   |   Role: " + model.role
                                color: "#aaaaaa"
                                font.pixelSize: 14
                            }
                        }

                        Button {
                            text: "Remove"
                            Layout.preferredWidth: 100
                            Layout.preferredHeight: 40
                            enabled: model.username !== "admin" 
                            
                            onClicked: {
                                adminManager.removeUser(model.username)
                            }
                        }
                    }
                }
            }
        }

        // ==========================================
        // CENTER: Visual Divider
        // ==========================================
        Rectangle {
            Layout.fillHeight: true
            Layout.preferredWidth: 2
            color: "#333333" 
        }

        // ==========================================
        // RIGHT SIDE: Registration Form
        // ==========================================
        ColumnLayout {
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.preferredWidth: parent.width * 0.4
            Layout.alignment: Qt.AlignTop
            spacing: 20

            Text {
                text: "Register New User"
                color: "white"
                font.pixelSize: 24
                font.bold: true
                Layout.bottomMargin: 10
            }

            TextField {
                id: firstNameInput
                placeholderText: "First Name"
                Layout.fillWidth: true
                font.pixelSize: 16
            }

            TextField {
                id: lastNameInput
                placeholderText: "Last Name"
                Layout.fillWidth: true
                font.pixelSize: 16
            }

            TextField {
                id: usernameInput
                placeholderText: "Username"
                Layout.fillWidth: true
                font.pixelSize: 16
            }

            TextField {
                id: passwordInput
                placeholderText: "Password"
                echoMode: TextInput.Password 
                Layout.fillWidth: true
                font.pixelSize: 16
            }

            ComboBox {
                id: roleInput
                model: ["Instructor", "Admin"]
                Layout.fillWidth: true
                font.pixelSize: 16
            }

            Item { Layout.fillHeight: true } 

            Text {
                id: statusMessage
                text: ""
                font.pixelSize: 14
                Layout.alignment: Qt.AlignHCenter
            }

            Button {
                text: "Add User"
                Layout.fillWidth: true
                Layout.preferredHeight: 50
                font.pixelSize: 18
                font.bold: true
                
                onClicked: {
                    if (firstNameInput.text === "" || lastNameInput.text === "" || 
                        usernameInput.text === "" || passwordInput.text === "") {
                        statusMessage.text = "All fields are required."
                        statusMessage.color = "#ff4444" // Red
                        return
                    }

                    let success = adminManager.registerUser(
                        firstNameInput.text, 
                        lastNameInput.text, 
                        roleInput.currentText, 
                        usernameInput.text, 
                        passwordInput.text
                    )

                    if (success) {
                        statusMessage.text = "User successfully registered."
                        statusMessage.color = "#00C851" // Green
                        
                        firstNameInput.text = ""
                        lastNameInput.text = ""
                        usernameInput.text = ""
                        passwordInput.text = ""
                    } else {
                        statusMessage.text = "Registration failed. Username may already exist."
                        statusMessage.color = "#ff4444" 
                    }
                }
            }
        }
    }
}