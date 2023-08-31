import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.12
import QtGraphicalEffects 1.0
import Message 1.0
import Chat 1.0
import QtQuick.Dialogs 1.2

Rectangle {
    property alias nameText: name.text
    property alias idText: lastMsg.text
    property string avatarId
    implicitHeight: Math.max(pic.implicitHeight+10,name.implicitHeight+lastMsg.implicitBackgroundHeight+15)
    color: "#FFFBFE"
    radius: 10
    Rectangle{
        id: pic
        width: 50
        height: 50
        implicitWidth: 50
        implicitHeight: 50
        radius: 10
        color: "#EADDFF"
        anchors{
            top: parent.top
            topMargin: 5
            left: parent.left
            leftMargin: 5
        }

        layer.enabled: true
        layer.effect: OpacityMask {
            maskSource: Rectangle {
                width: pic.width
                height: pic.height
                radius: pic.radius
            }
        }

        Image{
            cache: false
            source: {
                if(avatarId!=""){
                    "image://AvatarImgProvider/"+avatarId
                }
                else{
                    if(vm.chatType=="friend"){
                        "icons/person_FILL0_wght400_GRAD0_opsz40.png"
                    }
                    else if(vm.chatType=="group"){
                        "icons/group_FILL0_wght400_GRAD0_opsz40.png"
                    }
                }
            }
            anchors.fill: parent
        }
    }
    TextArea{
        id: name
        text: "FriendName"
        readOnly: true
        font.family: oppoSans.name
        font.bold: true
        anchors{
            bottom: pic.verticalCenter
            left: pic.right
            leftMargin: 5
            bottomMargin: -2
        }
    }
    TextArea{
        id: lastMsg
        text: "LastMessage"
        font.family: oppoSans.name
        readOnly: true
        anchors{
            top: pic.verticalCenter
            left: pic.right
            leftMargin: 5
            topMargin: -2
        }
    }
}
