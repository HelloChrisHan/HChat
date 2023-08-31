#ifndef MESSAGE_H
#define MESSAGE_H
#include<QString>
#include<QTime>
#include<QJsonObject>
#include"messagetype.h"

/*
完成人：张兆熙，韩闯
*/
class Message
{
public:
    Message();
    Message(MessageType,QString,QJsonObject);
    Message(QJsonObject messageJson);
    ~Message();
    MessageType type;
    QString time;
    QJsonObject content;

    QJsonObject messageJson;
};

#endif // MESSAGE_H

