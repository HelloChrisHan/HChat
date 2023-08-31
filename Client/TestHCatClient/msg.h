#ifndef MSG_H
#define MSG_H


//class Msg
//{
//public:
//    Msg();
//};
#include<QString>
#include<QTime>
#include<QJsonObject>

#include"messagetype.h"
class Msg
{
public:
    Msg();
    Msg(MessageType,QString,QJsonObject);
    Msg(QJsonObject JsonObject);
//    Msg(const Msg&);
    ~Msg();
    MessageType type;
    QString time;
    QJsonObject content;

    QJsonObject messageJson;
};

#endif // MSG_H
