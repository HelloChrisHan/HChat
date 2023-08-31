import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.12
import QtGraphicalEffects 1.0
import Message 1.0
import Chat 1.0
import QtQuick.Dialogs 1.2

Item {
    property Window rootWindow
    implicitWidth: 40+10
    Rectangle{
        id: me
        width: 40
        height: 40
        implicitWidth: 40
        implicitHeight: 40
        radius: 10
        color: "#ffffff"
        clip: true
        anchors{
            top: parent.top
            left: parent.left
//            margins: 5
        }
        layer.enabled: true
        layer.effect: OpacityMask {
            maskSource: Rectangle {
                width: me.width
                height: me.height
                radius: me.radius
            }
        }
//        Image{
//            anchors.fill: parent
//            source: "icons/logo.jpg"
//        }
    }

//    Image{
//        id: chat
//        source: "icons/sms_FILL0_wght400_GRAD0_opsz40.png"
//        anchors{
//            top: me.bottom
//            topMargin: 5
//            left: parent.left
////            margins: 5
//        }
//    }
    RoundButton{
        id: chat
        anchors{
            top: me.bottom
            topMargin: 20
            left: parent.left
        }

        height: 40
        width: 40
        implicitHeight: 40
        implicitWidth: 40
        radius: 10
        flat: true
//        background: Rectangle{
//            color: "#EADDFF"
//            radius: 10
//        }
        icon{
            source: "icons/music_note_FILL0_wght400_GRAD0_opsz40.png"
            width: 40
            height: 40
            color: "#21005D"
        }
        onClicked: {
            vm.playMusic()
        }
    }
//    Image{
//        id: friend
//        source: "icons/person_FILL0_wght400_GRAD0_opsz40.png"
//        anchors{
//            top: chat.bottom
//            topMargin: 5
//            left: parent.left
////            margins: 5
//        }
//    }
    RoundButton{
        id: friend
        anchors{
            top: chat.bottom
            topMargin: 5
            left: parent.left
        }

        height: 40
        width: 40
        implicitHeight: 40
        implicitWidth: 40
        radius: 10
        flat: true
//        background: Rectangle{
//            color: "#EADDFF"
//            radius: 10
//        }
        icon{
            source: "icons/person_FILL0_wght400_GRAD0_opsz40.png"
            width: 40
            height: 40
            color: "#21005D"
        }
        onClicked: {
            vm.chatType="friend"
        }
    }
//    Image{
//        id: group
//        source: "icons/group_FILL0_wght400_GRAD0_opsz40.png"
//        anchors{
//            top: friend.bottom
//            topMargin: 5
//            left: parent.left
////            margins: 5
//        }
//    }
    RoundButton{
        id: group
        anchors{
            top: friend.bottom
            topMargin: 5
            left: parent.left
        }

        height: 40
        width: 40
        implicitHeight: 40
        implicitWidth: 40
        radius: 10
        flat: true
//        background: Rectangle{
//            color: "#EADDFF"
//            radius: 10
//        }
        icon{
            source: "icons/group_FILL0_wght400_GRAD0_opsz40.png"
            width: 40
            height: 40
            color: "#21005D"
        }
        onClicked: {
            vm.chatType="group"
        }
    }
    RoundButton{
        id: crtGroup
        anchors{
            top: group.bottom
            topMargin: 5
            left: parent.left
        }

        height: 40
        width: 40
        implicitHeight: 40
        implicitWidth: 40
        radius: 10
        flat: true
//        background: Rectangle{
//            color: "#EADDFF"
//            radius: 10
//        }
        icon{
            source: "icons/group_add_FILL0_wght400_GRAD0_opsz40.png"
            width: 40
            height: 40
            color: "#21005D"
        }
        onClicked: {
            createGroupWin.open()
        }
    }
//    Dialog{
//        id: createButtonDialog
//        standardButtons: StandardButton.Yes|StandardButton.Cancel
//        onYes: {
//            vm.createGroup(groupName.text)
//        }
//        TextInput{
//            width: 300
//            id: groupName
//        }
//    }

    Popup{
        id: createGroupWin
        //        visible: !isLogin
        width: 400
        height: 240
        modal: true
        x: parent.x+50
//        anchors.centerIn: parent
        //        modality: Qt.ApplicationModal
        //        title: qsTr("Hello HChat!")

        background: Rectangle{
            anchors.fill: parent
            color: "white"
            radius: 10
            clip: true
        }

        Item{
            anchors.fill: parent

            TextArea{
                id: createGroupTitle
                text: "CreateGroup"
                readOnly: true
                font.family: oppoSans.name
                font.pixelSize: 50
                anchors{
                    horizontalCenter: parent.horizontalCenter
                    top: parent.top
                    margins: 10
                }
            }

            Rectangle{
                id: createGroupRect
                height: 50
                anchors{
                    left: parent.left
                    right: parent.right
                    top: createGroupTitle.bottom
                    margins: 10
                }

                implicitHeight: createGroupText.implicitHeight +20
                color: "#E8DEF8"
                radius: 20
                TextField{
                    id: createGroupText
                    anchors.fill: parent
                    anchors.margins: 10
                    background: Item{}
                    //font.family: oppoSans.name
                    placeholderText: "Group name"
                    font.family: oppoSans.name
                    echoMode: TextInput.Normal
//                    wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                    color: "#1D192B"
                }
            }

            RoundButton{
                id: createGroupBtn
                height: 50
                anchors{
                    left: parent.left
                    right: parent.right
                    top: createGroupRect.bottom
                    margins: 10
                }

                contentItem:  Text {
                    text: createGroupBtn.text
                    font: createGroupBtn.font
//                    opacity: enabled ? 1.0 : 0.3
//                    color: loginBtn.down ? "#17a81a" : "#21be2b"
                    color: "white"
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    elide: Text.ElideRight
                }
                text: "Apply"
                font.family: oppoSans.name

                background: Rectangle{
                    color: "#6750A4"
                    radius: 20
                }
                onClicked: {
                    vm.createGroup(createGroupText.text)
                    createGroupWin.close()
                }
            }
        }
    }



    RoundButton{
        id: settings
        anchors{
            left: parent.left
            bottom: parent.bottom
        }

        height: 40
        width: 40
        implicitHeight: 40
        implicitWidth: 40
        radius: 10
        flat: true
//        background: Rectangle{
//            color: "#EADDFF"
//            radius: 10
//        }
        icon{
            source: "icons/menu_FILL0_wght400_GRAD0_opsz40.png"
            width: 40
            height: 40
            color: "#21005D"
        }
        onClicked: {
            editInfo.open()
        }
    }
    Popup{
        id: editInfo
        width: 200
        height: 200
        modal: true
        x: settings.x
        y: settings.y+settings.height-height
        background: Rectangle{
            anchors.fill: parent
            color: "white"
            radius: 10
            clip: true
        }

        Item{
            anchors.fill: parent
            RoundButton{
                id: changeNameBtn
                anchors{
                    left: parent.left
                    right: parent.right
                    top: parent.top
                    bottom: parent.verticalCenter
                    margins: 10
                }
                contentItem:  Text {
                    text: changeNameBtn.text
                    font: changeNameBtn.font
                    color: "black"
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    elide: Text.ElideRight
                }
                text: "ChangeName"
                font.family: oppoSans.name
                flat: true
                radius: 10
                background: Rectangle{
                    color: "#E8DEF8"
                    radius: 10
                }
                onClicked: {
                    changeNameWin.open()
                    editInfo.close()
                }
            }
            RoundButton{
                id: changeAvatarBtn
                anchors{
                    left: parent.left
                    right: parent.right
                    top: parent.verticalCenter
                    bottom: parent.bottom
                    margins: 10
                }
                contentItem:  Text {
                    text: changeAvatarBtn.text
                    font: changeAvatarBtn.font
                    color: "black"
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    elide: Text.ElideRight
                }
                text: "ChangeAvatar"
                font.family: oppoSans.name
                flat: true
                radius: 10
                background: Rectangle{
                    color: "#E8DEF8"
                    radius: 10
                }
                onClicked: {
                    editInfo.close()
                    chooseAvatar.open()
                }
            }
        }
    }
    Popup{
        id: changeNameWin
        //        visible: !isLogin
        width: 400
        height: 240
        modal: true
        x: parent.x+50
//        anchors.centerIn: parent
        //        modality: Qt.ApplicationModal
        //        title: qsTr("Hello HChat!")

        background: Rectangle{
            anchors.fill: parent
            color: "white"
            radius: 10
            clip: true
        }

        Item{
            anchors.fill: parent

            TextArea{
                id: changeNameTitle
                text: "ChangeName"
                readOnly: true
                font.family: oppoSans.name
                font.pixelSize: 50
                anchors{
                    horizontalCenter: parent.horizontalCenter
                    top: parent.top
                    margins: 10
                }
            }

            Rectangle{
                id: changeNameRect
                height: 50
                anchors{
                    left: parent.left
                    right: parent.right
                    top: changeNameTitle.bottom
                    margins: 10
                }

                implicitHeight: changeNameText.implicitHeight +20
                color: "#E8DEF8"
                radius: 20
                TextField{
                    id: changeNameText
                    anchors.fill: parent
                    anchors.margins: 10
                    background: Item{}
                    placeholderText: "New Name"
                    font.family: oppoSans.name
                    echoMode: TextInput.Normal
//                    wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                    color: "#1D192B"
                }
            }

            RoundButton{
                id: applyChangeNameBtn
                height: 50
                anchors{
                    left: parent.left
                    right: parent.right
                    top: changeNameRect.bottom
                    margins: 10
                }

                contentItem:  Text {
                    text: applyChangeNameBtn.text
                    font: applyChangeNameBtn.font
//                    opacity: enabled ? 1.0 : 0.3
//                    color: loginBtn.down ? "#17a81a" : "#21be2b"
                    color: "white"
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    elide: Text.ElideRight
                }
                text: "Apply"
                font.family: oppoSans.name

                background: Rectangle{
                    color: "#6750A4"
                    radius: 20
                }
                onClicked: {
                    changeNameWin.close()
                    vm.changeName(changeNameText.text)
                    restartWin.open()
                }
            }
        }
    }
    FileDialog{
        id: chooseAvatar
        title: "Choose a avatar"
        nameFilters: ["*.jpg","*.png","*.gif"]
        onAccepted: {
            vm.changeAvatar(chooseAvatar.fileUrl)
            restartWin.open()
        }
    }
    Popup{
        id: restartWin
        //        visible: !isLogin
        width: 400
        height: 140
        modal: true
        x: parent.x+100
        closePolicy: Popup.NoAutoClose
//        anchors.centerIn: parent
        //        modality: Qt.ApplicationModal
        //        title: qsTr("Hello HChat!")

        background: Rectangle{
            anchors.fill: parent
            color: "white"
            radius: 10
            clip: true
        }

        Item{
            anchors.fill: parent

            TextArea{
                id: restartWinTitle
                text: "Changes need restart to apply"
                font.family: oppoSans.name
                font.pixelSize: 20
                anchors{
                    horizontalCenter: parent.horizontalCenter
                    top: parent.top
                    margins: 10
                }
            }

            RoundButton{
                id: restartWinBtn
                height: 50
                anchors{
                    left: parent.left
                    right: parent.right
                    top: restartWinTitle.bottom
                    margins: 10
                }

                contentItem:  Text {
                    text: restartWinBtn.text
                    font: restartWinBtn.font
//                    opacity: enabled ? 1.0 : 0.3
//                    color: loginBtn.down ? "#17a81a" : "#21be2b"
                    color: "white"
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    elide: Text.ElideRight
                }
                text: "Apply"
                font.family: oppoSans.name

                background: Rectangle{
                    color: "#6750A4"
                    radius: 20
                }
                onClicked: {
                    rootWindow.close()
                }
            }
        }
    }
}
