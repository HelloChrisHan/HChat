import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.12
import QtGraphicalEffects 1.0
import Message 1.0
import Chat 1.0
import QtQuick.Dialogs 1.2


Window {
    id: mainwin
    visible: true
    width: 1200
    height: 600
    minimumWidth: 620
    minimumHeight: 410
    title: qsTr("Hello HChat!")
    color: "transparent"
    //    flags: Qt.Window
    flags: Qt.FramelessWindowHint
    //    flags: Qt.CustomizeWindowHint|Qt.WindowSystemMenuHint
    property bool isLogin: false

    FontLoader{
        id: oppoSans
        source: "fonts/OPlusSans3-Medium.ttf"
//        name: "Ubuntu"
    }

    Rectangle{
        anchors.fill: parent
        color: "#CAC4D0"
        opacity: 0.8
        radius: 10
        clip: true
        //        FastBlur{
        //            anchors.fill: parent
        //            source: parent.parent.parent
        //            radius: 8
        //        }
    }
    //    ShaderEffectSource {
    //        id: effectSource
    //        sourceItem: mainwin
    //        anchors.fill: mainwin
    //        sourceRect: Qt.rect(x,y, width, height)
    //    }

    //    FastBlur{
    //        id: blur
    //        anchors.fill: effectSource

    //        source: effectSource
    //        radius: 8
    //    }



    TitleBar{
        rootWindow: mainwin
        id: titleBar
        anchors{
            left: parent.left
            right:parent.right
            top: parent.top
        }
    }

    NavigationBar{
        id: navBar
        rootWindow: mainwin
        anchors{
            top: titleBar.bottom
            left: parent.left
            bottom: parent.bottom
            margins: 10
        }
    }


    FriendPage{
        id: friendList
        anchors{
            top: titleBar.bottom
            left: navBar.right
            bottom: parent.bottom
            margins: 10
        }
        width: 300
    }

    ChatPage{
        chatTitleText: vm.chatName
        id: chatWin
        anchors{
            left: friendList.right
            top: titleBar.bottom
            right: parent.right
            bottom: parent.bottom
            margins: 10
        }
    }
    ResizeHandler{
        x:0
        y:0
        width: parent.width
        height: parent.height
        target: mainwin
    }
    Behavior on x{
        //        NumberAnimation{duration: 300}
        SmoothedAnimation{duration: 250}
    }
    Behavior on y{
        //        NumberAnimation{duration: 300}
        SmoothedAnimation{duration: 250}
    }
    Behavior on width{
        //        NumberAnimation{duration: 300}
        SmoothedAnimation{duration: 250}
    }
    Behavior on height{
        //        NumberAnimation{duration: 300}
        SmoothedAnimation{duration: 250}
    }


    Popup{
        id: loginWin
        //        visible: !isLogin
        width: 400
        height: 300
        modal: true
        anchors.centerIn: parent
        closePolicy: Popup.NoAutoClose
        //        modality: Qt.ApplicationModal
        //        title: qsTr("Hello HChat!")

        background: Rectangle{
            anchors.fill: parent
            color: "white"
            radius: 10
            clip: true
//            opacity: 0.2
//            FastBlur{
//                x: mainwin.contentItem.x
//                y: mainwin.contentItem.y
//                width: mainwin.contentItem.width
//                height: mainwin.contentItem.height
//                source: mainwin.contentItem
//                radius: 64
//                transparentBorder: false
//            }
        }

        Item{
            anchors.fill: parent
            RoundButton{
                anchors{
                    top: parent.top
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
                    source: "icons/close_FILL0_wght400_GRAD0_opsz40.png"
                    width: 30
                    height: 30
                    color: "#21005D"
                }
                onClicked: {
                    vm.logOut()
                    mainwin.close()
                }
            }

            Image{
                source: "icons/login_FILL0_wght400_GRAD0_opsz40.png"
                width: 50
                height: 50
                anchors{
                    right: loginTitle.left
                    verticalCenter: loginTitle.verticalCenter
                }
            }

            TextArea{
                id: loginTitle
                text: "Login"
                readOnly: true
                font.pixelSize: 50
                font.family: oppoSans.name
                anchors{
                    horizontalCenter: parent.horizontalCenter
                    top: parent.top
                    margins: 10
                }
            }

//            TextInput{
//                id: loginID
//                width: 300
//            }
            Rectangle{
                id: loginIdRect
                height: 50
                anchors{
                    left: parent.left
                    right: parent.right
                    top: loginTitle.bottom
                    margins: 10
                }

                implicitHeight: loginId.implicitHeight +20
                color: "#E8DEF8"
                radius: 20
                TextField{
                    id: loginId
                    anchors.fill: parent
                    anchors.margins: 10
                    background: Item{}
                    font.family: oppoSans.name
                    placeholderText: "ID"
                    echoMode: TextInput.Normal
//                    wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                    color: "#1D192B"
                }
            }
//            TextInput{
//                id: loginPwd
//                width: 300
//            }
            Rectangle{
                id: loginPwdRect
                height: 50
                anchors{
                    left: parent.left
                    right: parent.right
                    top: loginIdRect.bottom
                    margins: 10
                }

                implicitHeight: loginPwd.implicitHeight +20
                color: "#E8DEF8"
                radius: 20
                TextField{
                    id: loginPwd
                    anchors.fill: parent
                    anchors.margins: 10
                    background: Item{}
                    font.family: oppoSans.name
                    placeholderText: "Password"
                    echoMode: TextInput.Password
//                    wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                    color: "#1D192B"
                }
            }
//            TextInput{
//                id: name
//                width: 300
//            }
//            Button{
//                text: "login"
//                onClicked: {
//                    vm.login(loginId.text,loginPwd.text)
//                    loginWin.close()
//                }
//            }
            RoundButton{
                id: loginBtn
                height: 50
                anchors{
                    left: parent.left
                    right: parent.horizontalCenter
                    top: loginPwdRect.bottom
                    margins: 10
                }

//                text: "Login"
                contentItem:  Text {
                    text: loginBtn.text
                    font: loginBtn.font
//                    opacity: enabled ? 1.0 : 0.3
//                    color: loginBtn.down ? "#17a81a" : "#21be2b"
                    color: "white"
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    elide: Text.ElideRight
                }
                text: "Login"
                font.family: oppoSans.name

                background: Rectangle{
                    color: "#6750A4"
                    radius: 20
                }
                onClicked: {
                    vm.login(loginId.text,Qt.md5(loginPwd.text))
                    loginWin.close()
                }
            }

//            Button{
//                text: "regiester"
//                onClicked: {
//                    vm.regist(loginID.text,name.text,loginPwd.text)
//                }
//            }
            RoundButton{
                id: openRegisterBtn
                height: 50
                anchors{
                    left: parent.horizontalCenter
                    right: parent.right
                    top: loginPwdRect.bottom
                    margins: 10
                }

                text: "Register"
                font.family: oppoSans.name

                background: Rectangle{
                    color: "#E8DEF8"
                    radius: 20
                }
                onClicked: {
                    registerWin.open()
                }
            }
        }

    }

    Popup{
        id: registerWin
        //        visible: !isLogin
        width: 400
        height: 360
        modal: true
        anchors.centerIn: parent
        closePolicy: Popup.NoAutoClose
        //        modality: Qt.ApplicationModal
        //        title: qsTr("Hello HChat!")

        background: Rectangle{
            anchors.fill: parent
            color: "white"
            radius: 10
            clip: true
//            opacity: 0.2
//            FastBlur{
//                x: mainwin.contentItem.x
//                y: mainwin.contentItem.y
//                width: mainwin.contentItem.width
//                height: mainwin.contentItem.height
//                source: mainwin.contentItem
//                radius: 64
//                transparentBorder: false
//            }
        }

        Item{
            anchors.fill: parent
            RoundButton{
                anchors{
                    top: parent.top
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
                    source: "icons/close_FILL0_wght400_GRAD0_opsz40.png"
                    width: 30
                    height: 30
                    color: "#21005D"
                }
                onClicked: {
                    registerWin.close()
                }
            }

            TextArea{
                id: registerTitle
                text: "Register"
                readOnly: true
                font.pixelSize: 50
                font.family: oppoSans.name
                anchors{
                    horizontalCenter: parent.horizontalCenter
                    top: parent.top
                    margins: 10
                }
            }

            Rectangle{
                id: registerNameRect
                height: 50
                anchors{
                    left: parent.left
                    right: parent.right
                    top: registerTitle.bottom
                    margins: 10
                }

                implicitHeight: registerName.implicitHeight +20
                color: "#E8DEF8"
                radius: 20
                TextField{
                    id: registerName
                    anchors.fill: parent
                    anchors.margins: 10
                    background: Item{}
                    font.family: oppoSans.name
                    placeholderText: "Name"
                    echoMode: TextInput.Normal
//                    wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                    color: "#1D192B"
                }
            }

            Rectangle{
                id: registerIdRect
                height: 50
                anchors{
                    left: parent.left
                    right: parent.right
                    top: registerNameRect.bottom
                    margins: 10
                }

                implicitHeight: registerId.implicitHeight +20
                color: "#E8DEF8"
                radius: 20
                TextField{
                    id: registerId
                    anchors.fill: parent
                    anchors.margins: 10
                    background: Item{}
                    font.family: oppoSans.name
                    placeholderText: "ID"
                    echoMode: TextInput.Normal
//                    wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                    color: "#1D192B"
                }
            }

            Rectangle{
                id: registerPwdRect
                height: 50
                anchors{
                    left: parent.left
                    right: parent.right
                    top: registerIdRect.bottom
                    margins: 10
                }

                implicitHeight: registerPwd.implicitHeight +20
                color: "#E8DEF8"
                radius: 20
                TextField{
                    id: registerPwd
                    anchors.fill: parent
                    anchors.margins: 10
                    background: Item{}
                    font.family: oppoSans.name
                    placeholderText: "Password"
                    echoMode: TextInput.Password
//                    wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                    color: "#1D192B"
                }
            }

            RoundButton{
                id: registerBtn
                height: 50
                anchors{
                    left: parent.left
                    right: parent.right
                    top: registerPwdRect.bottom
                    margins: 10
                }

                contentItem:  Text {
                    text: registerBtn.text
                    font: registerBtn.font
//                    opacity: enabled ? 1.0 : 0.3
//                    color: loginBtn.down ? "#17a81a" : "#21be2b"
                    color: "white"
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    elide: Text.ElideRight
                }
                text: "Register"
                font.family: oppoSans.name

                background: Rectangle{
                    color: "#6750A4"
                    radius: 20
                }
                onClicked: {
                    vm.regist(registerId.text,registerName.text,Qt.md5(registerPwd.text))
                }
            }
        }
    }

    Component.onCompleted: {
        loginWin.open()
    }
}


