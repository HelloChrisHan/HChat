#ifndef SOCKETMANAGER_H
#define SOCKETMANAGER_H

#include <QObject>
#include <QTcpSocket>
//#include <vector>
#include <QTcpServer>
#include "message.h"
#include <QJsonDocument>
#include <QByteArray>

class SocketManager : public QObject
{
    Q_OBJECT
public:
    explicit SocketManager(QObject *parent = nullptr);
    static SocketManager* instance;
    QList<QTcpSocket*> sockets;
public:
    //通过SocketManager::getInstance()即可访问instance
    static SocketManager* getInstance();
    //当有新的客户都连接时，将对应的socket加入到sockets中
    void addSocket(QTcpSocket* socket);
    //根据ip获取socket
    QTcpSocket* findSocket(QString ip);
signals:
};

#endif // SOCKETMANAGER_H
