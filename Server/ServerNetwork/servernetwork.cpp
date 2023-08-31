#include "servernetwork.h"
#include "socketmanager.h"
#include<QDataStream>

ServerNetwork::ServerNetwork()
{
    //监听
    listen(QHostAddress::Any,8888);
}

// 服务端向客户端发送信息
void ServerNetwork::sendMessage(Message msg, QList<QString> receiverList)
{
    QJsonDocument jsonDoc(msg.messageJson);  // 将 QJsonObject 转换为 QJsonDocument
    QByteArray jsonData = jsonDoc.toJson();   // 将 QJsonDocument 序列化为 QByteArray

    QList<QString>::const_iterator it;
    for(it = receiverList.constBegin(); it != receiverList.constEnd(); ++it)
    {
        QString receiverIp = *it;
        SocketManager* sm = SocketManager::getInstance();
        QTcpSocket* socket = sm->findSocket(receiverIp);
        socket->waitForBytesWritten();
        socket->write(jsonData);
    }
}




//当有客户端连接到服务端时
//void ServerNetwork::clientConnect()
//{
//    qDebug()<<"client connect";
//    SocketManager*sm = SocketManager::getInstance();
//    QTcpSocket* client = this->nextPendingConnection();
//    sm->addSocket(client);

//    qDebug()<<"BUG1";

////    ClientSocket *cs = new ClientSocket(client);
////    QThread* thread = new QThread(this);
//    //当客户端向服务端发送信息时
//    connect(client, &QTcpSocket::readyRead ,[&](){
//        QByteArray data = client->readAll();
//        QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
//        QJsonObject jsonObj = jsonDoc.object();
//        Message msg = Message(jsonObj);
//        emit receiveMessageSignal(msg);
//    });

//    qDebug()<<"BUG2";

//    //当客户端断开连接时
////    connect(client, SIGNAL(disconnect()), cs, SLOT(deleteLater()));
////    connect(client, SIGNAL(disconnect()), thread, SLOT(quit()));
////    cs->moveToThread(thread);
//    //    thread->start();
//}

void ServerNetwork::incomingConnection(qintptr handle)
{
    qDebug()<<"client connect";
    SocketManager*sm = SocketManager::getInstance();
    auto client = new QTcpSocket(this);

    client->setSocketDescriptor(handle);
    sm->addSocket(client);
    qDebug()<<client->peerAddress().toString();
    //当客户端向服务端发送信息时
    connect(client, &QTcpSocket::readyRead,[&,client]{
        QByteArray data = client->readAll();
        QJsonDocument jsonDoc = QJsonDocument::fromJson(data);

        QJsonObject content = jsonDoc.object()["content"].toObject();
        MessageType type=static_cast<MessageType>(jsonDoc.object()["type"].toString().toInt());
        Message msg(type,"time",content);
        qDebug()<<"sadfadfas: "<<static_cast<int>(msg.type);
        emit receiveMessageSignal(msg);
    });

    connect(client,&QTcpSocket::disconnected,[&,client]{
       QString userIp = client->localAddress().toString();
       QJsonObject content;
       content["userIp"] = userIp;
       Message msg(MessageType::DISCONNECT,"time",content);
       emit receiveMessageSignal(msg);
    });

}
