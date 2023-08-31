#include "clientsocket.h"
#include "socketmanager.h"

ClientSocket::ClientSocket(QTcpSocket* socket, QObject *parent) : QObject(parent), socket(socket)
{
    //当客户端向服务端发送信息时
    //connect(socket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
}

//当客户端向服务端发送信息时
//void ClientSocket::onReadyRead()
//{
//    QByteArray data = socket->readAll();
//    QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
//    QJsonObject jsonObj = jsonDoc.object();
//    Message msg = Message(jsonObj);

//}
