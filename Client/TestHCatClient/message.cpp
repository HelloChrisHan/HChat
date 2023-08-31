#include "message.h"

Message::Message(
        bool isSelf,
        QString avatar,
        QString name,
        QString type,
        QString msg,
        QString emote,
        QString pic,
        QObject* parent
        ):
    m_isSelf(isSelf),
    m_avatar(avatar),
    m_name(name),
    m_type(type),
    m_msg(msg),
    m_emote(emote),
    m_pic(pic)
{

}

QString Message::msg()
{
    return m_msg;
}

QString Message::emote()
{
    return m_emote;
}

QString Message::pic()
{
    return m_pic;
}

QString Message::avatar()
{
    return m_avatar;
}

bool Message::isSelf()
{
    return m_isSelf;
}

void Message::setMsg(QString msg)
{
    if(msg == m_msg)
        return;
    m_msg = msg;
    emit msgChanged();
}

QString Message::type()
{
    return m_type;
}

QString Message::name()
{
    return m_name;
}
