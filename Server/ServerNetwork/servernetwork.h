#ifndef SERVERNETWORK_H
#define SERVERNETWORK_H

#include <QObject>
#include <QHostAddress>
#include <QThread>
#include <QJsonDocument>
#include <QByteArray>
#include "iservernetwork.h"
#include "clientsocket.h"
#include "message.h"

class ServerNetwork: public IServerNetwork
{
    Q_OBJECT

public:
    //构造函数
    ServerNetwork();

    //发送消息，让client接收
    void sendMessage(Message msg, QList<QString> receiverList);
public slots:
    //槽函数，客户端连接
//    void clientConnect();

    // QTcpServer interface
public:
    void incomingConnection(qintptr handle);
};

#endif // SERVERNETWORK_H
