/*
完成人：张兆熙
*/

#include "serverviewmodel.h"
#include "messagetype.h"
#include "userinfo.h"

ServerViewModel::ServerViewModel(IServerNetwork* serverNetwork):network(serverNetwork)
{
    database = new DataDB();
    connect(
        network,
        &IServerNetwork::receiveMessageSignal,
        [&](Message msg)
        {
            qDebug()<<static_cast<int>(msg.type);
            receiveMessage(msg);
        }
    );
}
/**
 * @brief ServerViewModel::receiveMessage 接受客户端信号，根据消息类型解析消息
 * @param msg 标准数据格式表示的消息
 * @return 是否成功
 */
/*
完成人：张兆熙
*/
bool ServerViewModel::receiveMessage(Message msg)
{
    //获取消息格式，作为解码判断标准
    MessageType type = msg.type;

    //如果消息格式为LOGIN，则按照登陆模式解码，下同
    if(type == MessageType::LOGIN)
        login(msg);
    else if(type == MessageType::REGISTER)
        regist(msg);
    else if(type == MessageType::CHANGE_PASSWORD)
        changePassword(msg);
    else if(type == MessageType::ADD_FRIEND)
        addFriend(msg);
    else if(type == MessageType::DELETE_FRIEND)
        removeFriend(msg);
    else if(type == MessageType::ADD_GROUP)
        joinGroup(msg);
    else if(type == MessageType::DELETE_GROUP)
        leaveGroup(msg);
    else if(type == MessageType::CS_TEXT)
        dealText(msg);
    else if(type == MessageType::CS_PICTURE)
        dealPicture(msg);
    else if(type == MessageType::CS_EMOT)
        dealEmot(msg);
    else if(type == MessageType::EDIT_GROUPO_INFO)
        editGroupInfo(msg);
    else if(type == MessageType::CREATE_GROUP)
        createGroup(msg);
    else if(type == MessageType::DISMISS_GROUP)
        dismissGroup(msg);
    else if(type == MessageType::QUIT_GROUP)
        leaveGroup(msg);
    else if(type == MessageType::JOIN_GROUP)
        joinGroup(msg);
    else if(type == MessageType::REQUEST_GROUP_INFO)
        requestGroupInfo(msg);
    else if(type == MessageType::REQUEST_FRIEND_INFO)
        requestFriendInfo(msg);
    else if(type == MessageType::DISCONNECT)
        disConnect(msg);
    else if(type == MessageType::EDIT_USER_INFO)
        editUserInfo(msg);
    else if(type == MessageType::VOICE)
        sendUserSound(msg);
    return true;
}

/*
完成人：张兆熙
*/
bool ServerViewModel::sendMessage(Message msg, QList<QString> receiverList)
{
    if(msg.type == MessageType::REGISTER)
    {
        QJsonObject content = msg.content;
        QString userIp = content["userIp"].toString();
        QList<QString> receiverIpList;
        receiverList.append(userIp);
        network->sendMessage(msg,receiverIpList);
    }
    else if(msg.type == MessageType::LOGIN)
    {
        QList<QString> receiverIpList;
        qint64 n = receiverList.size();
        for(int i = 0; i < n; i++)
        {
            receiverIpList.append(database->getIpAddress(receiverList[i]));
        }
        network->sendMessage(msg,receiverIpList);
        qDebug()<<static_cast<int>(msg.type)<<"ffffffffff";
        return true;
    }
    else
    {
        QList<QString> receiverIpList;
        qint64 n = receiverList.size();
        for(int i = 0; i < n; i++)
        {
            if(database->checkOnLine(receiverList[i]))
                receiverIpList.append(database->getIpAddress(receiverList[i]));
        }
        network->sendMessage(msg,receiverIpList);
        qDebug()<<static_cast<int>(msg.type)<<"ffffffffff";
        return true;
    }
    return false;
}

/*
完成人：张兆熙
*/
bool ServerViewModel::login(Message msg)
{
    QJsonObject content = msg.content;
    QString userIp = content["userIp"].toString();
    if(content["dataStructure"] == "QString")
    {
        QString userId = content["userId"].toString();
        QString password = content["password"].toString();
        qDebug()<<userIp;
        qDebug()<<userId;
        qDebug()<<password;
        QJsonObject outputContent;
        if(database->checkUserExistence(userId,password))
        {
            qDebug()<<"3";
            UserInfo userInfo = UserInfo(database->getUserInfo(userId));
            outputContent = conbineUserInfoIntoJson(userInfo);
            outputContent["condition"] = true;

            QList<QString> groupLists = userInfo.groupList;
            qDebug()<<groupLists.size() <<"---------------groupListsize";
        }
        else
        {
            qDebug()<<"4";
            outputContent["condition"] = false;
        }
        outputContent["dataStructure"] = "QString";
        outputContent["from"] = "Server";
        outputContent["to"] = content["from"];
        MessageType msgType = MessageType::LOGIN;
        QString time;
        Message msg = Message(msgType,time,outputContent);
        QList<QString> receiverList;
        receiverList.append(userId);
        database->login(userId,userIp);
        sendMessage(msg,receiverList);
        return true;
    }
    return false;
}

/*
完成人：张兆熙
*/
bool ServerViewModel::regist(Message msg)
{
    QJsonObject content = msg.content;
    QString userId = content["userId"].toString();
    if(!database->checkIdExist(userId))
    {
        qDebug()<<"HHHHHHHHHHHHHHHHHHHHH";
        QString password = content["password"].toString();
        QString name = content["name"].toString();
        QString userIp = content["userIp"].toString();
        database->regist(userId,password,name,userIp);
        QJsonObject returnContent;
        returnContent["condition"] = true;
        Message returnMessage = Message(MessageType::REGISTER,msg.time,returnContent);
        QList<QString> receiver;
        receiver.append(userId);
        sendMessage(returnMessage,receiver);
        qDebug()<<"FinishedDDDDDDDDDDDDDDDDDDD";
        return true;
    }
    QJsonObject returnContent;
    returnContent["condition"] = false;
    Message returnMessage = Message(MessageType::REGISTER,msg.time,returnContent);
    QList<QString> receiver;
    receiver.append(userId);
    sendMessage(returnMessage,receiver);
    return false;
}

/*
完成人：张兆熙
*/
bool ServerViewModel::changePassword(Message msg)
{
    QJsonObject content = msg.content;
    if(content["dataStructure"] == "QString")
    {
        QString userId = content["userId"].toString();
        QString newPassword = content["newPassword"].toString();
        QString oldPassword = content["oldPassword"].toString();
        if(database->checkUserExistence(userId,oldPassword))
        {
            database->changePassword(userId,newPassword);

            QJsonObject returnContent;
            returnContent["condition"] = true;
            //            msg.content = returnContent;
            Message message(msg.type,msg.time,returnContent);
            QList<QString> receiverList;
            receiverList.append(userId);
            sendMessage(message,receiverList);
            return true;
        }
        else
        {
            QJsonObject returnContent;
            returnContent["condition"] = false;
            //            msg.content = returnContent;
            Message message(msg.type,msg.time,returnContent);
            QList<QString> receiverList;
            receiverList.append(userId);
            sendMessage(message,receiverList);
        }
    }

    return false;
}

/*
完成人：张兆熙
*/
QJsonObject ServerViewModel::conbineUserInfoIntoJson(UserInfo userInfo)
{
    QJsonObject content;
    content["userId"] = userInfo.userId;
    content["password"] = userInfo.password;
    content["name"] = userInfo.name;
    content["avatar"] = userInfo.picture;

    QJsonArray friendListJson;
    foreach(const QString &item, userInfo.friendList) {
        friendListJson.append(item);
    }

    QJsonArray groupListJson;
    foreach(const QString &item, userInfo.groupList) {
        groupListJson.append(item);
    }

    content["friendList"] = friendListJson;
    content["groupList"] = groupListJson;

    qDebug()<<"JSON size" <<groupListJson.size();


    return content;
}

/*
完成人：张兆熙
*/
QJsonObject ServerViewModel::conbineGroupInfoIntoJson(GroupInfo groupInfo)
{
    QJsonObject content;
    content["groupId"] = groupInfo.groupId;
    content["ownerId"] = groupInfo.ownerId;
    content["name"] = groupInfo.name;
    content["picture"] = QString::fromUtf8(groupInfo.picture);

    QList<QString> groupMembers = database->getGroupMembers(groupInfo.groupId);
    QJsonArray groupMembersJson;
    foreach(const QString &item, groupMembers) {
        groupMembersJson.append(item);
    }

    content["groupMembers"] = groupMembersJson;

    return content;
}

/*
完成人：张兆熙
*/
bool ServerViewModel::addFriend(Message msg)
{
    QJsonObject content = msg.content;
    QString userId1 = content["userId1"].toString();
    QString userId2 = content["userId2"].toString();
    if(!database->isFriend(userId1,userId2))
    {
        database->addFriend(userId1,userId2);
        database->addFriend(userId2,userId1);

        QJsonObject content1;
        QJsonObject content2;

        UserInfo userInfo1 = database->getUserInfo(userId2);
        UserInfo userInfo2 = database->getUserInfo(userId1);

        content1 = conbineUserInfoIntoJson(userInfo1);
        content2 = conbineUserInfoIntoJson(userInfo2);
        content1["requestType"] = "friend";
        content2["requestType"] = "friend";
        content1["condition"] = true;
        content2["condition"] = true;


        Message msg1 = Message(MessageType::SC_USER_INFO,msg.time,content1);
        QList<QString> receiverList1;
        receiverList1.append(userId1);
        sendMessage(msg1,receiverList1);

        Message msg2 = Message(MessageType::SC_USER_INFO,msg.time,content2);
        QList<QString> receiverList2;
        receiverList2.append(userId2);
        sendMessage(msg2,receiverList2);

        return true;
    }

    return false;
}

/*
完成人：张兆熙
*/
bool ServerViewModel::joinGroup(Message msg)
{
    qDebug()<<"Enter joingroup";
    QJsonObject content = msg.content;
    QString userId = content["userId"].toString();
    QString groupId = content["groupId"].toString();
    if(!database->checkInGroup(userId,groupId))
    {
        database->joinGroup(groupId,userId);

        //        GroupInfo groupInfo = database->getGroupInfo(groupId);
        //        QJsonObject outputContent = conbineGroupInfoIntoJson(groupInfo);
        //        QList<QString> receiverList;
        //        receiverList.append(userId);        Message message1(msg.type,msg.time,outputContent);
        //        sendMessage(message1,receiverList);

        //        UserInfo userInfo = database->getUserInfo(userId);
        //        outputContent = conbineUserInfoIntoJson(userInfo);
        //        receiverList = database->getGroupMembers(groupId);
        //        Message message2(msg.type,msg.time,outputContent);
        //        sendMessage(message2,receiverList);

        //        QList<QString> groupMembers = database->getGroupMembers(groupId);
        //        QList<QJsonObject> groupMembersInfo;
        //        qint64 n = groupMembers.size();
        //        QJsonObject tempJson;
        //        for(int i = 0; i < n; i++)
        //        {
        //            tempJson["name"] = database->getUserInfo(groupMembers[i]).name;
        //            tempJson["userId"] = database->getUserInfo(groupMembers[i]).userId;
        //            tempJson["picture"] = QString::fromUtf8(database->getUserInfo(groupMembers[i]).picture);
        //            groupMembersInfo.append(tempJson);
        //        }
        //        QJsonArray jsonArray;
        //        for (const QJsonObject &obj : groupMembersInfo) {
        //            jsonArray.append(obj);
        //        }
        //        QJsonObject finalObject;
        //        finalObject["groupMembersList"] = jsonArray;
        //        Message finalMessage(MessageType::SC_GROUPMEMBERS_INFO,msg.time,finalObject);
        //        receiverList = {};
        //        receiverList.append(userId);
        //        sendMessage(finalMessage,receiverList);


        QList<QString> receiverList = database->getGroupMembers(groupId);
        GroupInfo groupInfo = database->getGroupInfo(groupId);
        QJsonObject outputContent = conbineGroupInfoIntoJson(groupInfo);
        QJsonArray groupMemberListJsonArray;
        for (const QString &obj : receiverList) {
            groupMemberListJsonArray.append(obj);
        }
        outputContent["groupMembersList"] = groupMemberListJsonArray;
        outputContent["groupMemberList"] = groupMemberListJsonArray;
        outputContent["MembersList"] = groupMemberListJsonArray;
        outputContent["MemberList"] = groupMemberListJsonArray;

        Message outputMessage(MessageType::SC_GROUP_INFO,msg.time,outputContent);
        sendMessage(outputMessage,receiverList);
        return true;
    }
    return false;
}

/*
完成人：张兆熙
*/
bool ServerViewModel::removeFriend(Message msg)
{
    QJsonObject content = msg.content;
    if(content["dataStructure"] == "QString")
    {
        QString userId1 = content["userId1"].toString();
        QString userId2 = content["userId2"].toString();
        database->removeFriend(userId1,userId2);


        QJsonObject content1;
        QJsonObject content2;

        UserInfo userInfo1 = database->getUserInfo(userId2);
        UserInfo userInfo2 = database->getUserInfo(userId1);

        content1 = conbineUserInfoIntoJson(userInfo1);
        content2 = conbineUserInfoIntoJson(userInfo2);
        content1["requestType"] = "friend";
        content2["requestType"] = "friend";
        content1["condition"] = true;
        content2["condition"] = true;


//        Message msg1 = Message(MessageType::SC_USER_INFO,msg.time,content1);
//        QList<QString> receiverList1;
//        receiverList1.append(userId1);
//        sendMessage(msg1,receiverList1);

//        Message msg2 = Message(MessageType::SC_USER_INFO,msg.time,content2);
//        QList<QString> receiverList2;
//        receiverList2.append(userId2);
//        sendMessage(msg2,receiverList2);
        return true;
    }
    return false;
}

/*
完成人：张兆熙
*/
bool ServerViewModel::leaveGroup(Message msg)
{
    QJsonObject content = msg.content;
    if(content["dataStructure"] == "QString")
    {
        QString userId = content["userId"].toString();
        QString groupId = content["groupId"].toString();
        database->leaveGroup(groupId,userId);
        return true;
    }
    return false;
}

/*
完成人：张兆熙
*/
bool ServerViewModel::dealText(Message msg)
{
    QJsonObject content = msg.content;

    if(content["dataStructure"] == "QString")
    {
        QString receiverId = content["to"].toString();
        QList<QString> receiverList;
        if(content.contains("group"))
        {
            QString groupId = content["group"].toString();
            GroupInfo groupInfo = database->getGroupInfo(groupId);
            QString ownerId = groupInfo.ownerId;
            QString senderId = content["from"].toString();
            receiverList = database->getGroupMembers(groupId);
            receiverList.removeAll(senderId);
//            receiverList.removeOne(ownerId);
            content["groupId"] = groupId;
            Message returnMsg(MessageType::SC_TEXT,msg.time,content);
            sendMessage(returnMsg,receiverList);
            return true;
        }
        else
        {
            receiverList.append(receiverId);
            Message returnMsg(MessageType::SC_TEXT,msg.time,content);
            sendMessage(returnMsg,receiverList);
            return true;
        }
    }
    return false;
}

/*
完成人：张兆熙
*/
bool ServerViewModel::dealPicture(Message msg)
{
    QJsonObject content = msg.content;
    if(content["dataStructure"] == "picture")
    {
        QByteArray picture = content["picture"].toString().toUtf8();
        QString pictureId = database->addPicture(picture);
        QString receiver = content["to"].toString();
        content["pictureId"] = pictureId;

        QByteArray compressedPicture = compressPicture(picture);
        content["picture"] = QString::fromUtf8(compressedPicture);

        msg.content = content;
        QList<QString> receiverList;

        msg.type = MessageType::SC_PICTURE;
        msg.messageJson["type"] = QString::number(int(MessageType::SC_PICTURE));
        if(content.contains("group"))
        {
            QString groupId = content["group"].toString();
            receiverList = database->getGroupMembers(groupId);
            receiverList.append(content["from"].toString());
            Message message(msg.type,msg.time,content);
            sendMessage(message,receiverList);
            return true;
        }
        else
        {
            receiverList.append(receiver);
            receiverList.append(content["from"].toString());
            Message message(msg.type,msg.time,content);
            sendMessage(message,receiverList);
            return true;
        }
    }
    return false;
}

/*
完成人：张兆熙
*/
bool ServerViewModel::dealEmot(Message msg)
{
    QJsonObject content = msg.content;
    msg.type = MessageType::SC_EMOT;
    msg.messageJson["type"] = QString::number(int(MessageType::SC_EMOT));
    QString receiverId = content["to"].toString();
    QList<QString> receiverList;
    if(content.contains("group"))
    {
        QString groupId = content["group"].toString();
        GroupInfo groupInfo = database->getGroupInfo(groupId);
        QString ownerId = groupInfo.ownerId;
        QString senderId = content["from"].toString();
        receiverList = database->getGroupMembers(groupId);
        receiverList.removeAll(senderId);
//        receiverList.removeOne(ownerId);
        sendMessage(msg,receiverList);
        return true;
    }
    else
    {
        receiverList.append(receiverId);
        sendMessage(msg,receiverList);
        return true;
    }
return false;
}

/*
完成人：张兆熙
*/
bool ServerViewModel::editGroupInfo(Message msg)
{
    QJsonObject content = msg.content;
    QString groupId = content["groupId"].toString();
    if(content["dataStructure"] == "newName")
    {
        QString name = content["newName"].toString();
        database->setGroupName(groupId,name);
    }
    else if(content["dataStructure"] == "newPicture")
    {
        QByteArray picture = content["newPicture"].toString().toUtf8();
        database->setGroupPicture(groupId,picture);
    }

    GroupInfo groupInfo = database->getGroupInfo(groupId);
    QJsonObject outputContent = conbineGroupInfoIntoJson(groupInfo);
    Message outputMessage(MessageType::SC_GROUP_INFO,msg.time,outputContent);

    QList<QString> receiverList = database->getGroupMembers(groupId);
    sendMessage(outputMessage,receiverList);

    return true;
}

/*
完成人：张兆熙
*/
bool ServerViewModel::createGroup(Message msg)
{
    QJsonObject content = msg.content;
    if(content["dataStructure"] == "QString")
    {
        QString ownerId = content["userId"].toString();
        QByteArray picture = content["picture"].toString().toUtf8();
        QString name = content["name"].toString();
        QString groupId = database->createGroup(ownerId,name,picture);
        //        content["group"] = groupId;
        //        msg.content = content;
        QList<QString> receiverList;
        receiverList.append(content["userId"].toString());

        GroupInfo groupInfo = database->getGroupInfo(groupId);
        QJsonObject groupInfoJson = conbineGroupInfoIntoJson(groupInfo);
        Message outputMessage = Message(MessageType::SC_GROUP_INFO,msg.time,groupInfoJson);
        sendMessage(outputMessage,receiverList);
        qDebug()<<receiverList[0] <<"ddddddddddddddddddddd";
        return true;
    }
    return false;
}

/*
完成人：张兆熙
*/
bool ServerViewModel::dismissGroup(Message msg)
{
    QJsonObject content = msg.content;
    if(content["dataStructure"] == "QString")
    {
        QString groupId = content["groupId"].toString();
        QList<QString> receiverList = database->getGroupMembers(groupId);
        database->dismissGroup(groupId);
        QJsonObject outputContent;
        content["groupId"] = groupId;
        Message outputMessage(msg.type,msg.time,outputContent);
        sendMessage(outputMessage,receiverList);
        return true;
    }

    return false;
}

/*
完成人：张兆熙
*/
bool ServerViewModel::requestFriendInfo(Message msg)
{
    qDebug()<<"HHHHHHH";
    QJsonObject content = msg.content;
    QString userId = content["userId"].toString();
    qDebug()<<userId<<" <---ID";
    UserInfo userInfo = database->getUserInfo(userId);
    QJsonObject outputContent;
    outputContent["userId"] = userInfo.userId;
    outputContent["name"] = userInfo.name;
//    outputContent["picture"] = QString::fromUtf8(userInfo.picture);
    outputContent["avatar"] = userInfo.picture;
    qDebug()<<outputContent["avatar"]<<"AVATAR HERE";
    outputContent["requestType"] = content["requestType"];
    Message returnMessage(MessageType::SC_USER_INFO,msg.time,outputContent);
    QList<QString> receiverList;
    receiverList.append(content["from"].toString());
    sendMessage(returnMessage,receiverList);
    return true;
}

/*
完成人：张兆熙
*/
bool ServerViewModel::requestGroupInfo(Message msg)
{
    QJsonObject content = msg.content;
    QString groupId = content["groupId"].toString();
    QString userId = msg.content["from"].toString();
    GroupInfo groupInfo = database->getGroupInfo(groupId);
    QJsonObject outputContent = conbineGroupInfoIntoJson(groupInfo);
    QList<QString> groupMembersList = database->getGroupMembers(groupId);
    QJsonArray groupMembersJsonArray;
    foreach(const QString &item, groupMembersList)
    {
        groupMembersJsonArray.append(item);
    }
    outputContent["groupMembers"] = groupMembersJsonArray;
    Message returnMessage(MessageType::SC_GROUP_INFO,msg.time,outputContent);
    QList<QString> receiverList;
    receiverList.append(userId);
    sendMessage(returnMessage,receiverList);
    return true;
}

/*
完成人：张兆熙
*/
bool ServerViewModel::editUserInfo(Message msg)
{
    QJsonObject content = msg.content;
    if(content["dataStructure"].toString() == "newPicture")
    {
        QString userId = content["userId"].toString();
        QString picture = content["newPicture"].toString();
        database->editUserAvatar(userId,picture);
//        content["avatar"] = QString::fromUtf8(picture);
//        content["picture"] = QString::fromUtf8(picture);
//        Message outputMessage(MessageType::EDIT_USER_INFO,"time",content);
//        QList<QString> receiverList;
//        receiverList.append(userId);
//        sendMessage(outputMessage,receiverList)
    }
    else if(content["dataStructure"] == "newName")
    {
        QString userId = content["userId"].toString();
        QString name = content["newName"].toString();
        database->editUserName(userId,name);
    }
    return true;
}

/*
完成人：张兆熙
*/
bool ServerViewModel::sendUserSound(Message msg)
{
    QJsonObject content = msg.content;
    QString from = content["from"].toString();
    QString to = content["to"].toString();
    Message outputMessage(MessageType::VOICE,"time",content);
    QList<QString> receiverList;
    receiverList.append(to);
    sendMessage(outputMessage,receiverList);
}

/*
完成人：张兆熙
*/
bool ServerViewModel::disConnect(Message msg)
{
    QJsonObject content = msg.content;
    QString userIp = content["userIp"].toString();
    database->offLine(userIp);
    return true;
}

/*
完成人：张兆熙
*/
QByteArray ServerViewModel::compressPicture(QByteArray pic)
{
    qint16 len = pic.size();
    QByteArray compressedPicture = "";
    for(int i = 0; i < len; i++)
    {
        if(i % 4 == 0)
            compressedPicture += pic[i];
    }
    return compressedPicture;
}
