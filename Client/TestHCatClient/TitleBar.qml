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
    property point startPoint;
    implicitHeight: 40//24+5

    MouseArea{
        anchors.fill: parent
        onPressed: {
            startPoint.x = mouse.x
            startPoint.y = mouse.y
        }

        onPositionChanged: {
            rootWindow.x = rootWindow.x - (startPoint.x- mouse.x);
            rootWindow.y = rootWindow.y - (startPoint.y -mouse.y);
        }
    }
//    height: implicitHeight
//    Image{
//        id: close
//        source: "icons/close_FILL0_wght400_GRAD0_opsz40.png"
//        width: 24
//        height: 24
////        implicitWidth: 24
////        implicitHeight: 24
//        anchors{
//            top: parent.top
//            right: parent.right
//            margins: 5
//        }
//    }
    RoundButton{
        id: close
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
            rootWindow.close()
        }
    }
//    Image{
//        id: max
//        source: "icons/fullscreen_FILL0_wght400_GRAD0_opsz40.png"
//        width: 24
//        height: 24
////        implicitWidth: 24
////        implicitHeight: 24
//        anchors{
//            top: parent.top
//            right: close.left
//            margins: 5
//        }
//    }
    RoundButton{
        id: max
        anchors{
            top: parent.top
            right: close.left
            margins: 10
        }

        height: 30
        width: 30
        implicitHeight: 30
        implicitWidth: 30
        radius: 10
        flat: true
        icon{
            source: "icons/fullscreen_FILL0_wght400_GRAD0_opsz40.png"
            width: 30
            height: 30
            color: "#21005D"
        }
        onClicked: {
            if(rootWindow.visibility == Window.Maximized){
                rootWindow.showNormal()
            }
            else{
                rootWindow.showMaximized()
            }
        }
    }
//    Image{
//        id: min
//        source: "icons/remove_FILL0_wght400_GRAD0_opsz40.png"
//        width: 24
//        height: 24
////        implicitWidth: 24
////        implicitHeight: 24
//        anchors{
//            top: parent.top
//            right: max.left
//            margins: 5
//        }
//    }

    RoundButton{
        id: min
        anchors{
            top: parent.top
            right: max.left
            margins: 10
        }

        height: 30
        width: 30
        implicitHeight: 30
        implicitWidth: 30
        radius: 10
        flat: true
        icon{
            source: "icons/remove_FILL0_wght400_GRAD0_opsz40.png"
            width: 30
            height: 30
            color: "#21005D"
        }
        onClicked: {
            rootWindow.showMinimized()
        }
    }


}
