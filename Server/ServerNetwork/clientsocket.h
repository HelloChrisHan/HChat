#ifndef CLIENTSOCKET_H
#define CLIENTSOCKET_H

#include <QObject>
#include <QTcpSocket>
#include "message.h"
#include "servernetwork.h"

class ClientSocket : public QObject
{
    Q_OBJECT
public:
    //构造函数
    explicit ClientSocket(QTcpSocket* socket, QObject *parent = nullptr);
private:
    //封装socket
    QTcpSocket *socket;
//public slots:
//    //槽函数，当客户都安向服务端发送信息时调用
//    void onReadyRead();
};

#endif // CLIENTSOCKET_H
