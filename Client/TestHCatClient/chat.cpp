#include "chat.h"

Chat::Chat(QString name, QString id, QString avatar): m_name(name),m_id(id),m_avatar(avatar)
{

}

QString Chat::name()
{
    return m_name;
}

QString Chat::id()
{
    return m_id;
}

QString Chat::avatar()
{
    return m_avatar;
}
