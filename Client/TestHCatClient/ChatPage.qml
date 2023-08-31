import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.12
import QtGraphicalEffects 1.0
import Message 1.0
import Chat 1.0
import QtQuick.Dialogs 1.2

Rectangle {
    property alias chatTitleText: chatTitle.text
    color: "#FFFBFE"
    radius: 10


    ListView{
        id: chatList
        anchors {
            left: parent.left
            right: parent.right
            top: parent.top
            bottom: inputBox.top
        }
        verticalLayoutDirection: ListView.BottomToTop
        model: vm.lsMsg
        clip: true
        delegate: MessageBlock{
            anchors.left: parent.left
            anchors.right: parent.right
            msgType: model.type
            emoteId: model.emote
            isSelf: model.self
            nameText: model.name
            msgText: model.msg
            avatarId: model.avatar
        }
    }

//    Rectangle{
//        id: blurEffect
//        height: titleRect.implicitHeight
//        anchors{
//            left: parent.left
//            right: parent.right
//            top: parent.top
//        }
//        radius: 10
//        clip: true
//        FastBlur{
//            x: chatList.x
//            y: chatList.y
//            width: chatList.width
//            height: chatList.height
//            source: chatList
//            radius: 64
//            transparentBorder: false
//        }
//    }

    Rectangle{
        id: titleRect
        anchors{
            left: parent.left
            right:parent.right
            top: parent.top
        }
        implicitHeight: chatPic.implicitHeight+10
        color: "#FFFBFE"
        radius: 10
//        opacity: 0.5

        Rectangle{
            id: chatPic
            width: 50
            height: 50
            implicitWidth: 50
            implicitHeight: 50
            radius: 10
            anchors{
                left: parent.left
                leftMargin: 5
                top: parent.top
                topMargin: 5
            }
            color: "#EADDFF"

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
                    if(vm.chatAvatar!=""){
                        "image://AvatarImgProvider/"+vm.chatAvatar
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
            id: chatTitle
            text: "ChatTitle"
            font.family: oppoSans.name
            font.pixelSize: 30
            color: "#1C1B1F"
            readOnly: true
            anchors{
                verticalCenter: parent.verticalCenter
                left: chatPic.right
                leftMargin: 5
            }
        }
//        Image {
//            id: chatInfo
//            source: "icons/more_horiz_FILL0_wght400_GRAD0_opsz40.png"
//            anchors{
//                verticalCenter: parent.verticalCenter
//                right: parent.right
//                margins: 5
//            }
//        }
        RoundButton{
            id: chatInfo
            anchors{
                verticalCenter: parent.verticalCenter
                right: parent.right
                margins: 5
            }

            height: 50
            width: 50
            implicitHeight: 50
            implicitWidth: 50
            radius: 10
            flat: true
    //        background: Rectangle{
    //            color: "#EADDFF"
    //            radius: 10
    //        }
            icon{
                source: "icons/stadia_controller_FILL0_wght400_GRAD0_opsz40.png"
                width: 50
                height: 50
                color: "#21005D"
            }
            onClicked: {
                Qt.openUrlExternally("file:/home/kiddin/Desktop/hchat_new/TestHCatClient/TestHCatClient/game/minigame_origin/play.html")
//                Qt.openUrlExternally("file:/home/kiddin/Desktop/game/minigame_origin/play.html")
            }
        }
    }

    Rectangle{
        id: inputBox
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        implicitHeight: Math.max(inputRect.implicitHeight+10,send.implicitHeight+10)
        color: "#FFFBFE"
        radius: 10

        RoundButton{
            id: emote
            anchors{
                left: parent.left
                bottom: parent.bottom
                margins: 5
            }

            height: 37
            width: 37
            implicitHeight: 37
            implicitWidth: 37
            radius: 10
//            text: "send"
            background: Rectangle{
                color: "#E8DEF8"
                radius: 10
            }
            icon{
                source: "icons/mood_FILL0_wght400_GRAD0_opsz40.png"
                width: 37
                height: 37
                color: "#1D192B"
            }
            onClicked: {
//                vm.sendEmote("1.jpg")
                emotePage.open()
            }
        }

        RoundButton{
            id: picture
            anchors{
                left: emote.right
                bottom: parent.bottom
                margins: 5
            }

            height: 37
            width: 37
            implicitHeight: 37
            implicitWidth: 37
            radius: 10
//            text: "send"
            background: Rectangle{
                color: "#E8DEF8"
                radius: 10
            }
            icon{
                source: "icons/volume_up_FILL0_wght400_GRAD0_opsz40.png"
                width: 37
                height: 37
                color: "#1D192B"
            }
            onClicked: {
                vm.sendSound()
            }
        }


        Rectangle{
            id: inputRect
            anchors.left: picture.right
            anchors.leftMargin: 5
            anchors.right: send.left
            anchors.rightMargin: 5
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 5
            implicitHeight: input.implicitHeight +15
            color: "#E8DEF8"
            radius: 20
            TextField{
                id: input
                anchors.fill: parent
                anchors.margins: 10
                background: Item{}
                font.family: oppoSans.name
                padding: 0
//                implicitHeight: 17
                placeholderText: "Input to send"
                font.pixelSize: 15
                wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                color: "#1D192B"
            }
        }

        RoundButton{
            id: send
            anchors.right: parent.right
            anchors.rightMargin: 5
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 5
            height: 37
            width: 37
            implicitHeight: 37
            implicitWidth: 37
            radius: 10
//            text: "send"
            background: Rectangle{
                color: "#6750A4"
                radius: 10
            }

            onClicked: sendAndErase()
            function sendAndErase(){
                if(input.text!=""){
                    vm.sendMessage(input.text)
                    input.text=""
                }
            }

            icon{
                source: "icons/send_FILL0_wght400_GRAD0_opsz40.png"
                width: 37
                height: 37
                color: "#FFFFFF"
            }
        }

    }

    Popup{
        id: emotePage
        width: parent.width/1.6
        height: parent.height/2
        anchors.centerIn: parent
        modal: true
        background: Rectangle{
            anchors.fill: parent
            color: "white"
            radius: 10
        }
        GridView{
            model: 43
            anchors.fill: parent
            anchors.centerIn: parent
            clip: true
            cellWidth: 80
            cellHeight: 80
            delegate: Button{
                height: 80
                width: 80
                background: Rectangle{
                    anchors.fill: parent
                    color: "white"
                }

                Image{
                    source: "emotes/"+(index+1)+".gif"
                    anchors.fill: parent
                    anchors.margins: 10
                }
                onClicked: {
                    vm.sendEmote((index+1)+".gif")
                    emotePage.close()
                }
            }
        }
    }
}
