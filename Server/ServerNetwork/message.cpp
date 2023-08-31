#include "message.h"
#include <QtDebug>
Message::Message()
{

}
/*
完成人：张兆熙，韩闯
*/
Message::Message(MessageType _type, QString _time, QJsonObject _content):
    type(_type),
    time(_time),
    content(_content)
{
    messageJson["type"] = QString::number(static_cast<int>(type));
    messageJson["time"] = time;
    messageJson["content"] = content;
}

/*
完成人：张兆熙，韩闯
*/
Message::Message(QJsonObject messageJson)
{
    type = static_cast<MessageType>(messageJson["type"].toString().toInt());
    qDebug()<<"the type: "<<messageJson["type"];
    time = messageJson["time"].toString();
    content = messageJson["content"].toObject();
    this->messageJson = messageJson;
}

Message::~Message()
{
//    qDebug()<<"message transmittion finished" << endl;
}
