import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.12
import QtGraphicalEffects 1.0
import Message 1.0
import Chat 1.0
import QtQuick.Dialogs 1.2

Item {
    property alias nameText: name.text
    property alias msgText: message.text
    property string emoteId
    property string msgType
    property string avatarId
    id: msgBox
    clip: false
    implicitHeight: Math.max(pic.implicitHeight+10,nameAndMsg.height)
    implicitWidth: pic.implicitWidth+nameAndMsg.implicitWidth+10
    Rectangle{
        id: pic
        width: 50
        height: 50
        implicitHeight: 50
        implicitWidth: 50
        color: "#EADDFF"
        radius: 10
        anchors.top: parent.top
        anchors.topMargin: 5
        anchors.right: parent.right
        anchors.rightMargin: 5

        layer.enabled: true
        layer.effect: OpacityMask {
            maskSource: Rectangle {
                width: chatPic.width
                height: chatPic.height
                radius: chatPic.radius
            }
        }

        Image{
            cache: false
            source: {
                if(avatarId!=""){
                    "image://AvatarImgProvider/user:"+avatarId
                }
                else{
                    "icons/person_FILL0_wght400_GRAD0_opsz40.png"
                }
            }
            anchors.fill: parent
        }
    }

    Item {
        id: nameAndMsg
        anchors.rightMargin: 0
        anchors.top: parent.top
        anchors.topMargin: 0
        anchors.right: pic.left
        implicitHeight: name.implicitHeight+msgBackground.implicitHeight+15
        implicitWidth: Math.max(name.implicitWidth+10,msgBackground.implicitWidth+10)

        Text {
            id: name
            text: "You"
            font.family: oppoSans.name
            anchors.top: parent.top
            anchors.topMargin: 5
            anchors.right: parent.right
            anchors.rightMargin: 5
            color: "#1C1B1F"
        }

        Rectangle {
            id: msgBackground
            implicitWidth: {
                if(msgType==="text"){
                    message.implicitWidth
                }
                else if(msgType==="emote"){
                    emote.implicitWidth
                }
            }
            implicitHeight: {
                if(msgType==="text"){
                    message.implicitHeight
                }
                else if(msgType==="emote"){
                    emote.implicitHeight
                }
            }
            color: {
                if(msgType==="text"){
                    "#625B71"
                }
                else if(msgType==="emote"){
                    "transparent"
                }
            }

            radius: 10
            anchors.top: name.bottom
            anchors.topMargin: 5
            anchors.right: parent.right
            anchors.rightMargin: 5
            clip: true

            layer.enabled: true
            layer.effect: OpacityMask {
                maskSource: Rectangle {
                    width: msgBackground.width
                    height: msgBackground.height
                    radius: msgBackground.radius
                }
            }

            TextArea {
                id: message
                visible: (msgType==="text")? true:false
                width: msgBox.width-140
                x: 0
                y: 0
                text: "SomeMessages"
                font.family: oppoSans.name
                wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                readOnly: true
                color: "#FFFFFF"
            }
            Image{
                id: emote
                visible: (msgType==="emote")? true:false
                x:0
                y:0
                source: "emotes/"+emoteId
            }
//            Image{
//                id: pic
//                visible: false
//                x:0
//                y:0
//                source: ""
//            }
        }
    }
}
