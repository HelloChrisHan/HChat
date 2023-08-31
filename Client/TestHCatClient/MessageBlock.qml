import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.12
import QtGraphicalEffects 1.0
import Message 1.0
import Chat 1.0
import QtQuick.Dialogs 1.2

Item {
    property bool isSelf: false
    property string nameText: "Someone"
    property string msgText: "SomeMessages"
    property string msgType: "text"
    property string emoteId: ""
    property string avatarId: ""
    implicitHeight: Math.max(otherMsg.implicitHeight,selfMsg.implicitHeight)
    OthersMessage{
        id: otherMsg
        msgType: parent.msgType
        nameText: parent.nameText
        msgText: parent.msgText
        emoteId: parent.emoteId
        avatarId: parent.avatarId
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        width: parent.width
        visible: isSelf? false : true
    }
    SelfMessage{
        id: selfMsg
        msgType: parent.msgType
        nameText: parent.nameText
        msgText: parent.msgText
        emoteId: parent.emoteId
        avatarId: parent.avatarId
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        width: parent.width
        visible: isSelf? true : false
    }
    Component.onCompleted: {
        console.log(emoteId)
    }
}
