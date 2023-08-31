import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.12
import QtGraphicalEffects 1.0
import Message 1.0
import Chat 1.0
import QtQuick.Dialogs 1.2

Item {

    Item{
        id: searchPane
        implicitHeight: searchRect.implicitHeight
        anchors{
            left: parent.left
            right: parent.right
            top: parent.top
        }

        Rectangle{
            id: searchRect
            anchors{
                left: parent.left
                right: searchBtn.left
                rightMargin: 5
                top: parent.top
            }
            implicitHeight: searchText.implicitHeight+20
            color: "#FFFBFE"
            radius: 20

            TextField{
                id: searchText
                placeholderText: "Add Friend/Group"
                background: Item{}
                font.family: oppoSans.name
                padding: 0

                implicitHeight: 17
                anchors.fill: parent
                anchors.margins: 10
                font.pixelSize: 15
                color: "#1C1B1F"
            }
        }
        RoundButton{
            id: searchBtn
            width: 37
            height: 37
            implicitHeight: 37
            implicitWidth: 37
            radius: 20
            anchors{
                right: parent.right
                top: parent.top
            }
            background: Rectangle{
                color: "#FFFBFE"
                radius: 20
            }
            icon{
                source: "icons/search_FILL0_wght400_GRAD0_opsz40.png"
                color: "#1C1B1F"
            }
            onClicked: {
                if(vm.chatType=="friend"){
                    console.log("add friend")
                    vm.addFriend(searchText.text)
                }
                else if(vm.chatType=="group"){
                    console.log("add group")
                    vm.addGroup(searchText.text)
                }
            }
        }
    }

    ListView{
        id: chatList
        anchors{
            left: parent.left
            right: parent.right
            top: searchPane.bottom
            topMargin: 5
            bottom: parent.bottom
        }
        layer.enabled: true
        layer.effect: OpacityMask {
            maskSource: Rectangle {
                width: chatList.width
                height: chatList.height
                radius: 10
            }
        }

//        anchors.margins: 5
        clip: true
        model: (vm.chatType=="friend")? vm.lsFriend : vm.lsGroup
        spacing:5
        delegate: FriendBlock{
            nameText: name
            idText: "Id: "+id
            anchors.left: parent.left
            anchors.right: parent.right
            avatarId: model.avatar
//            opacity: 0.5
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    parent.ListView.view.currentIndex = index
                    vm.selectChat(id,name,avatar)
                    console.log(index)
                }
            }
            RoundButton{
                id: deleteChatBtn
                anchors{
                    verticalCenter: parent.verticalCenter
                    right: parent.right
                    margins: 10
                }

                height: 30
                width: 30
                implicitHeight: 30
                implicitWidth: 30
                radius: 10
                flat: true
                icon{
                    source: "icons/cancel_FILL0_wght400_GRAD0_opsz40.png"
                    width: 30
                    height: 30
                    color: "#21005D"
                }
                onClicked: {
                    if(vm.chatType=="friend"){
                        vm.removeFriend(index)
                    }
                    else if(vm.chatType=="group"){
                        vm.leaveGroup(index)
                    }
                }
            }
        }
//        highlight: Rectangle{
//            anchors.fill: parent.currentItem
//            color: "blue"
//            radius: 0
//        }
//        highlightFollowsCurrentItem: true
    }
}
