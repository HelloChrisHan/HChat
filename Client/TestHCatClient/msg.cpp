//#include "msg.h"

//Msg::Msg()
//{

//}

#include "msg.h"
#include <QtDebug>
Msg::Msg()
{

}

Msg::Msg(MessageType _type, QString _time, QJsonObject _content):
    type(_type),
    time(_time),
    content(_content)
{
    messageJson["type"] = QString::number(static_cast<int>(type));
    messageJson["time"] = time;
    messageJson["content"] = content;
}

Msg::Msg(QJsonObject messageJson)
{
    type = static_cast<MessageType>(messageJson["type"].toString().toInt());
    time = messageJson["time"].toString();
    content = messageJson["content"].toObject();
    this->messageJson = messageJson;
}

//Msg::Msg(const Msg &msg)
//{
//    type=msg.type;
//    time=msg.time;
//    content=msg.content;
//    messageJson=msg.messageJson;
//}

Msg::~Msg()
{
//    qDebug()<<"message transmittion finished" << endl;
}
