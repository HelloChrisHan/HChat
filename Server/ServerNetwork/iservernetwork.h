#ifndef ISERVERNETWORK_H
#define ISERVERNETWORK_H
#include <QObject>
#include <QString>
#include <QTcpServer>
#include "message.h"


class IServerNetwork:public QTcpServer
{
    Q_OBJECT
public:
    //发送消息，让client接收
    virtual void sendMessage(Message msg, QList<QString> receiverList)=0;
signals:
    //接受来自client的信息
    void receiveMessageSignal(Message msg);
};
#endif // ISERVERNETWORK_H
