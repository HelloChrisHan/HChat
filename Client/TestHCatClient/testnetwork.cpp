#include "IClientNetwork.h"
#include "testnetwork.h"
#include "msg.h"
#include "messagetype.h"

#include<QHostAddress>
#include<QThread>
#include<QTimer>
#include<QBuffer>

TestNetwork::TestNetwork(QObject *parent)
{
    socket = new QTcpSocket();
}

bool TestNetwork::connectToServer(){
    //QTcpSocket *socket = new QTcpSocket(this); // 创建QTcpSocket对象
    socket->connectToHost("192.168.27.1", 8888); // 连接到指定服务器和端口

    if (socket->waitForConnected(5000)) { // 等待连接成功
        qDebug() << "Connected to server!";
//        QByteArray requestData = "Hello, server!"; // 待发送数据
//        socket->write(requestData); // 发送数据
//        socket->waitForBytesWritten(); // 等待数据发送完成

//        QByteArray responseData;
//        while(socket->waitForReadyRead()) { // 等待接收数据
//            responseData.append(socket->readAll());
//        }
//        qDebug() << "Response from server: " << responseData;
//        return true;
    } else {
        qDebug() << "Connection failed!";
//        return false;
    }

    connect(
        socket,
        &QTcpSocket::readyRead,
        [&](){
//        //QThread::msleep(500);
        QByteArray data = socket->readAll();
        QJsonDocument temp = QJsonDocument::fromJson(data);
        QJsonObject content = temp.object()["content"].toObject();
        MessageType type = static_cast<MessageType>(temp.object()["type"].toString().toInt());
        qDebug()<<static_cast<int>(type)<<" <---TYPE";
        if(type == MessageType::SC_TEXT)
        {
            QString userId = content["from"].toString();
            //            QString userName = content[""]
            QString text = content["text"].toString();
            if(!content.contains("group"))
            {
                emit receiveUserTextSignal(userId, text);
            }
            else
            {
                QString groupId = content["group"].toString();
                QString userId = content["from"].toString();
                QString textMsg = content["text"].toString();
                emit receiveGroupTextSignal(groupId,userId,textMsg);
            }
        }
        else if(type == MessageType::SC_EMOT)
        {
            qDebug()<<"WOW";
            QString userId = content["from"].toString();
            QString emot = content["emot"].toString();
            if(!content.contains("group"))
            {
                emit receiveUserEmoteSignal(userId,emot);
            }
            else
            {
                QString groupId = content["group"].toString();
                QString userId = content["from"].toString();
                QString emot = content["emot"].toString();
                emit receiveGroupEmoteSignal(groupId,userId,emot);
            }
        }
        else if(type == MessageType::SC_PICTURE)
        {
            QString userId = content["from"].toString();
            QByteArray picture = content["picture"].toString().toUtf8();
            QString pictureId = content["pictureId"].toString();
            if(!content.contains("group"))
            {
                QImage img;
                img.loadFromData(picture);
                emit receiveUserPictureSignal(userId,img);
                emit receiveUserPictureIdSignal(userId,pictureId);
            }
            else
            {
                QImage img;
                img.loadFromData(picture);
                QString groupId = content["group"].toString();
                emit receiveGroupPictureSignal(groupId,UserId,img);
                emit receiveGroupPictureIdSignal(groupId,userId,pictureId);
            }
        }

        else if(type == MessageType::ADD_GROUP)
        {
            QString name = content["name"].toString();
            QByteArray avatar = content["avatar"].toString().toUtf8();
            QJsonArray jsonArray = content["membersList"].toArray();
            QImage img;
            img.loadFromData(avatar);
            QList<QString> membersList;
            qint32 n = jsonArray.size();
            for(int i = 0 ; i < n ; i++)
            {
                membersList.append(jsonArray[i].toString());
            }
            emit joinGroupSignal(name,img,membersList);
        }
        else if(type == MessageType::EDIT_GROUPO_INFO)
        {
            QString groupId = content["groupId"].toString();
            QString name = content["name"].toString();
            QByteArray avatar = content["picture"].toString().toUtf8();
//            QList<QString> groupMembers;
//            QJsonArray jsonArray = content["members"].toArray();
//            qint32 n = jsonArray.size();
//            for(int i = 0 ; i < n ; i++)
//            {
//                groupMembers.append(jsonArray[i].toString());
//            }
            QImage imgMsg;
            imgMsg.loadFromData(avatar);
            emit editGroupInfoSignal(groupId,name,imgMsg);
        }
        else if(type == MessageType::DISMISS_GROUP)
        {
            QString groupId = content["groupId"].toString();
            emit dismissGroupSignal(groupId);
        }
        else if(type == MessageType::LOGIN)
        {
            bool isSuccess = content["condition"].toBool();
            QString name = content["name"].toString();
            QString str = content["avatar"].toString();
            qDebug()<<str<<"111111111111111111111111111";
            QByteArray picture = str.toLatin1();
            QImage avatar;
            avatar.loadFromData(QByteArray::fromBase64(picture.mid(str.indexOf(",")+1)));
            qDebug()<<avatar.width()<<"22222222222222222222222222222";

            QJsonArray jsonArray = content["friendList"].toArray();
            QList<QString> friendList;
            for (const QJsonValue &value : jsonArray) {
                if (value.isString()) {
                    QString stringValue = value.toString();
                    friendList.append(stringValue);
                } else {
                    qDebug() << "Array element is not a string.";
                }
            }

            jsonArray = content["groupList"].toArray();
            QList<QString> groupList;
            for (const QJsonValue &value : jsonArray) {
                if (value.isString()) {
                    QString stringValue = value.toString();
                    groupList.append(stringValue);
                } else {
                    qDebug() << "Array element is not a string.";
                }
            }

            qDebug()<<isSuccess<<name;
            emit loginSignal(isSuccess,name,avatar,friendList,groupList);

        }
        else if(type == MessageType::SC_USER_INFO)
        {
            QString userId = content["userId"].toString();
            QString name = content["name"].toString();
            QString type = content["requestType"].toString();
            QString str = content["avatar"].toString();

            qDebug()<<str<<"111111111111111111111111111";
            QByteArray picture = str.toLatin1();
            QImage avatar;
            avatar.loadFromData(QByteArray::fromBase64(picture.mid(str.indexOf(",")+1)));
            qDebug()<<avatar.width()<<"22222222222222222222222222222";

            emit receiveFriendInfoSignal(name,avatar,userId,type);
        }
        else if(type == MessageType::SC_GROUP_INFO)
        {
            QString name = content["name"].toString();
            QString groupId = content["groupId"].toString();
            QByteArray picture = content["avatar"].toString().toUtf8();
            QImage avatar;
            avatar.loadFromData(picture);
            QList<QString> memberList;
            QJsonArray array = content["groupMembers"].toArray();
            qint32 n = array.size();
            for(int i = 0 ; i < n ; i++)
            {
                memberList.append(array[i].toString());
            }

            qDebug()<<name <<"  " << "AVATAR" << groupId <<"  " << memberList.size();
            emit receiveGroupInfoSignal(name,avatar,groupId,memberList);
        }
        else if(type == MessageType::CHANGE_PASSWORD)
        {
            bool isSuccess = content["condition"].toBool();
            emit changePasswordSignal(isSuccess);
        }
        else if(type == MessageType::VOICE)
        {
            emit receivedSoundSignal();
        }

    }
    );
    return true;
    //socket->close(); // 关闭Socket连接
}

bool TestNetwork::disConnect(){

    socket->close();// 关闭Socket连接

    return true;
}

void TestNetwork::login(QString userId, QString pwd){
    this->UserId = userId;
    QJsonObject content;
    qDebug()<<userId;
    qDebug()<<pwd;
    content["userIp"] = socket->localAddress().toString();
    content["userId"] = userId;
    content["password"] = pwd;
    content["dataStructure"] = "QString";
    Msg msg(MessageType::LOGIN,"time",content);
    QJsonDocument tempDocument(msg.messageJson);
    QByteArray finalMsg = tempDocument.toJson();
    socket->waitForBytesWritten();
    //QThread::msleep(500);
    socket->write(finalMsg);
};

void TestNetwork::regist(QString userId, QString name, QString pwd){
    QJsonObject content;
    content["userIp"] = socket->localAddress().toString();
    content["userId"] = userId;
    content["password"] = pwd;
    content["name"] = name;
    content["dataStructure"] = "QString";

    //need a function to accquire ip here

    Msg msg(MessageType::REGISTER,"time",content);
    QJsonDocument tempDocument(msg.messageJson);
    QByteArray finalMsg = tempDocument.toJson();
    socket->waitForBytesWritten();
    //QThread::msleep(500);
    socket->write(finalMsg);
};

void TestNetwork::changePwd(QString oldPwd, QString newPwd){
    QJsonObject content;
    content["olsPassword"] = oldPwd;
    content["newPassword"] = newPwd;
    content["dataStructure"] = "QString";

    Msg msg(MessageType::CHANGE_PASSWORD,"time",content);
    QJsonDocument tempDocument(msg.messageJson);
    QByteArray finalMsg = tempDocument.toJson();
    socket->waitForBytesWritten();
    //QThread::msleep(500);
    socket->write(finalMsg);
}

void TestNetwork::addFriend(QString userId){
    QJsonObject content;
    content["userId1"] = UserId;
    content["userId2"] = userId;
    content["dataStructure"] = "QString";

    Msg msg(MessageType::ADD_FRIEND,"time",content);
    QJsonDocument tempDocument(msg.messageJson);
    QByteArray finalMsg = tempDocument.toJson();
    socket->waitForBytesWritten();
    //QThread::msleep(500);
    socket->write(finalMsg);
}

void TestNetwork::joinGroup(QString groupId){
    QJsonObject content;
    content["userId"] = UserId;
    content["groupId"] = groupId;
    content["dataStructure"] = "QString";

    Msg msg(MessageType::ADD_GROUP,"time",content);
    QJsonDocument tempDocument(msg.messageJson);
    QByteArray finalMsg = tempDocument.toJson();
    socket->waitForBytesWritten();
    //QThread::msleep(500);
    socket->write(finalMsg);
}

void TestNetwork::removeFriend(QString userId){
    QJsonObject content;
    content["userId1"] = UserId;
    content["userId2"] = userId;
    content["dataStructure"] = "QString";

    Msg msg(MessageType::DELETE_FRIEND,"time",content);
    QJsonDocument tempDocument(msg.messageJson);
    QByteArray finalMsg = tempDocument.toJson();
    socket->waitForBytesWritten();
    //QThread::msleep(500);
    socket->write(finalMsg);
}

void TestNetwork::leaveGroup(QString groupId){
    QJsonObject content;
    content["userId"] = UserId;
    content["groupId"] = groupId;
    content["dataStructure"] = "QString";

    Msg msg(MessageType::QUIT_GROUP,"time",content);
    QJsonDocument tempDocument(msg.messageJson);
    QByteArray finalMsg = tempDocument.toJson();
    socket->waitForBytesWritten();
    //QThread::msleep(500);
    socket->write(finalMsg);
}

void TestNetwork::createGroup(QString groupName){
    QJsonObject content;
    content["userId"] = UserId;
    content["name"] = groupName;
    content["dataStructure"] = "QString";

    Msg msg(MessageType::CREATE_GROUP,"time",content);
    QJsonDocument tempDocument(msg.messageJson);
    QByteArray finalMsg = tempDocument.toJson();
    socket->waitForBytesWritten();
    //QThread::msleep(500);
    socket->write(finalMsg);
}

void TestNetwork::editGroupName(QString groupId, QString groupName){
    QJsonObject content;
    content["groupId"] = groupId;
    content["name"] = groupName;
    content["dataStructure"] = "newName";

    //probably a little problem

    Msg msg(MessageType::EDIT_GROUPO_INFO,"time",content);
    QJsonDocument tempDocument(msg.messageJson);
    QByteArray finalMsg = tempDocument.toJson();
    socket->waitForBytesWritten();
    //QThread::msleep(500);
    socket->write(finalMsg);
}

void TestNetwork::editGroupAvatar(QString groupId, QImage groupAvatar){
    QJsonObject content;
    content["groupId"] = groupId;
    //QByteArray temp = groupAvatar.convertToFormat("PNG");
    //content["newPicture"] = temp;
    //remain question

    content["dataStructure"] = "newPicture";

    //probably no problem

    Msg msg(MessageType::EDIT_GROUPO_INFO,"time",content);
    QJsonDocument tempDocument(msg.messageJson);
    QByteArray finalMsg = tempDocument.toJson();
    socket->waitForBytesWritten();
    //QThread::msleep(500);
    socket->write(finalMsg);
}

void TestNetwork::dismissGroup(QString groupId){
    QJsonObject content;
    content["groupId"] = groupId;
    content["dataStructure"] = "QString";

    Msg msg(MessageType::DISMISS_GROUP,"time",content);
    QJsonDocument tempDocument(msg.messageJson);
    QByteArray finalMsg = tempDocument.toJson();
    socket->waitForBytesWritten();
    //QThread::msleep(500);
    socket->write(finalMsg);
}

void TestNetwork::sendUserText(QString userId, QString text){
    QJsonObject content;
    content["from"] = UserId;
    content["to"] = userId;
    content["text"] = text;
    content["dataStructure"] = "QString";

    Msg msg(MessageType::CS_TEXT,"time",content);
    QJsonDocument tempDocument(msg.messageJson);
    QByteArray finalMsg = tempDocument.toJson();
    socket->waitForBytesWritten();
    //QThread::msleep(500);
    socket->write(finalMsg);
}

void TestNetwork::sendGroupText(QString groupId, QString text){
    QJsonObject content;
    content["from"] = UserId;
    content["userId"] = UserId;
    content["group"] = groupId;
    content["text"] = text;
    content["dataStructure"] = "QString";

    Msg msg(MessageType::CS_TEXT,"time",content);
    QJsonDocument tempDocument(msg.messageJson);
    QByteArray finalMsg = tempDocument.toJson();
    socket->waitForBytesWritten();
    //QThread::msleep(500);
    socket->write(finalMsg);
}

void TestNetwork::sendUserImage(QString userId, QImage image){
    QJsonObject content;
    content["from"] = UserId;
    content["dataStructure"] = "picture";
    content["to"] = userId;
    //need a convert function

    Msg msg(MessageType::CS_PICTURE,"time",content);
    QJsonDocument tempDocument(msg.messageJson);
    QByteArray finalMsg = tempDocument.toJson();
    socket->waitForBytesWritten();
    //QThread::msleep(500);
    socket->write(finalMsg);
}

void TestNetwork::sendGroupImage(QString groupId, QImage image){
    QJsonObject content;
    content["from"] = UserId;
    content["dataStructure"] = "picture";
    content["group"] = groupId;
    //need a convert function

    Msg msg(MessageType::CS_PICTURE,"time",content);
    QJsonDocument tempDocument(msg.messageJson);
    QByteArray finalMsg = tempDocument.toJson();
    socket->waitForBytesWritten();
    //QThread::msleep(500);
    socket->write(finalMsg);
}

void TestNetwork::sendUserEmote(QString userId, QString emoteId){
    QJsonObject content;
    content["from"] = UserId;
    content["to"] = userId;
    content["emot"] = emoteId;
    content["dataStructure"] = "emot";

    Msg msg(MessageType::CS_EMOT,"time",content);
    QJsonDocument tempDocument(msg.messageJson);
    QByteArray finalMsg = tempDocument.toJson();
    socket->waitForBytesWritten();
    //QThread::msleep(500);
    socket->write(finalMsg);
}

void TestNetwork::sendGroupEmote(QString groupId, QString emoteId){
    QJsonObject content;
    content["from"] = UserId;
    content["group"] = groupId;
    content["emot"] = emoteId;
    content["dataStructure"] = "emot";

    Msg msg(MessageType::CS_EMOT,"time",content);
    QJsonDocument tempDocument(msg.messageJson);
    QByteArray finalMsg = tempDocument.toJson();
    socket->waitForBytesWritten();
    //QThread::msleep(500);
    socket->write(finalMsg);
}

void TestNetwork::createGroup(QString name, QImage image)
{
    QJsonObject content;
    content["name"] = name;
    content["userId"] = this->UserId;
    QByteArray byteArray;
    QBuffer buffer(&byteArray);
    buffer.open(QIODevice::WriteOnly);
    image.save(&buffer, "PNG");
    content["picture"] = QString::fromUtf8(byteArray);
    content["dataStructure"] = "QString";
    Msg msg(MessageType::CREATE_GROUP, "time", content);
    QJsonDocument tempDocument(msg.messageJson);
    QByteArray finalMsg = tempDocument.toJson();
    socket->waitForBytesWritten();
    //QThread::msleep(500);
    socket->write(finalMsg);
}

void TestNetwork::requestFriendInfo(QString friendId, QString type)
{
    QJsonObject content;
    content["from"] = this->UserId;
    content["userId"] = friendId;
    content["dataStructure"] = "QString";
    content["requestType"] = type;

    Msg msg(MessageType::REQUEST_FRIEND_INFO,"time",content);
    QJsonDocument tempDocument(msg.messageJson);
    QByteArray finalMsg = tempDocument.toJson();
//    qDebug()<<"request type: "<<tempDocument.object()["type"].toString();

    socket->waitForBytesWritten();
    socket->write(finalMsg);
//    QThread::msleep(500);
//    QTimer::singleShot(
//        500,
//        this,
//        [=]{
//            qDebug()<<friendId<<" <---REQUEST";
//            socket->write(finalMsg);
//        }
//    );

}

void TestNetwork::requestGroupInfo(QString groupId)
{
    QJsonObject content;
    content["from"] = this->UserId;
    content["dataStructure"] = "QString";
    content["groupId"] = groupId;
    Msg msg(MessageType::REQUEST_GROUP_INFO,"time",content);
    QJsonDocument tempDocument(msg.messageJson);
    QByteArray finalMsg = tempDocument.toJson();
    socket->waitForBytesWritten();
    socket->write(finalMsg);
}

void TestNetwork::editAvatar(QImage avatar)
{
    avatar=avatar.scaled(50,50);
    QJsonObject content;
    content["userId"] = UserId;
    QByteArray temp;
    QBuffer buffer(&temp);
    buffer.open(QIODevice::WriteOnly);
    avatar.save(&buffer,"JPG");
//    QString avatarStr = temp.constData();

    qDebug()<<"Change Avatar!";

    content["newPicture"] = QString::fromLatin1(temp.toBase64().data());
    qDebug()<<content["newPicture"].toString().size()<<"++++++++++++++++++++++++";
    content["dataStructure"] = "newPicture";


    Msg msg(MessageType::EDIT_USER_INFO,"time",content);
    QJsonDocument tempDocument(msg.messageJson);
    QByteArray finalMsg = tempDocument.toJson();
    socket->waitForBytesWritten();
    //QThread::msleep(500);
    socket->write(finalMsg);
}

void TestNetwork::editName(QString name)
{
    QJsonObject content;
    content["userId"] = UserId;
    content["newName"] = name;
    content["dataStructure"] = "newName";

    Msg msg(MessageType::EDIT_USER_INFO,"time",content);
    QJsonDocument tempDocument(msg.messageJson);
    QByteArray finalMsg = tempDocument.toJson();
    socket->waitForBytesWritten();
    //QThread::msleep(500);
    socket->write(finalMsg);
}

void TestNetwork::sendUserSound(QString userId)
{
    QJsonObject content;
    content["from"]=UserId;
    content["to"]=userId;

    Msg msg(MessageType::VOICE,"time",content);
    QJsonDocument tempDocument(msg.messageJson);
    QByteArray finalMsg = tempDocument.toJson();
    socket->waitForBytesWritten();
    //QThread::msleep(500);
    socket->write(finalMsg);
}


/*void TestNetwork::sendUserTextSignal(){
    QObject::connect(this , &TestNetwork::receiveUserTextSignal
                     &receiver , slot);

    emit receiveUserTextSignal(QString friendId, QString userId, QString userName, QString textMsg);
}

void TestNetwork::receiveUserPictureSignal(){
    QObject::connect(this , &TestNetwork::receiveUserPictureSignal
                     &receiver , slot);

    emit receiveUserPictureSignal(QString friendId, QString userId, QString userName, QImage imgMsg);
}

void TestNetwork::receiveUserEmoteSignal(){
    QObject::connect(this , &TestNetwork::receiveUserEmoteSignal
                     &receiver , slot);

    emit receiveUserEmoteSignal(QString friendId, QString userId, QString userName, QString emoteMsg);
}

void TestNetwork::receiveGroupTextSignal(){
    QObject::connect(this , &TestNetwork::receiveUserTextSignal
                     &receiver , slot);

    emit receiveGroupTextSignal(QString groupId, QString userId, QString userName, QString textMsg);
}

void TestNetwork::receiveGroupPictureSignal(){
    QObject::connect(this , &TestNetwork::receiveGroupPictureSignal
                     &receiver , slot);

    emit receiveGroupTextSignal(QString groupId, QString userId, QString userName, QString imgMsg);
}

void TestNetwork::receiveGroupEmoteSignal(){
    QObject::connect(this , &TestNetwork::receiveGroupEmoteSignal
                     &receiver , slot);

    emit receiveGroupEmoteSignal(QString groupId, QString userId, QString userName, QString emoteMsg);
}*/
