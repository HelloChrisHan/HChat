#include "socketmanager.h"
#include <QDebug>

//通过SocketManager::getInstance()即可访问instance
SocketManager* SocketManager::instance = 0;
SocketManager* SocketManager::getInstance()
{
    if(instance == nullptr)
        instance = new SocketManager();
    return instance;
}

//构造函数
SocketManager::SocketManager(QObject *parent) : QObject(parent)
{

}

//当有新的客户都连接时，将对应的socket加入到sockets中
void SocketManager::addSocket(QTcpSocket* socket)
{
    sockets.push_back(socket);
}

//根据ip获取socket
QTcpSocket* SocketManager::findSocket(QString ip)
{
//    std::vector<QTcpSocket*>::iterator it;
//    for(it = sockets.begin(); it != sockets.end(); it++)
//    {
//        QTcpSocket* socket = *it;
//        if ((socket->peerAddress()).toString() == ip)
//        {
//            return socket;
//        }
//    }
    foreach(QTcpSocket* i,sockets){
        if(i->peerAddress().toString().contains(ip)){
            return i;
        }
    }
    qDebug() << "该ip不存在或未连接服务器。";
    return NULL;
}
