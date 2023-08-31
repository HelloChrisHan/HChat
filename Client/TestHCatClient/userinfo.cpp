#include "userinfo.h"

UserInfo::UserInfo(QString userId, QString name, QString avatar)
    :m_userId(userId),m_name(name),m_avatar(avatar)
{

}

QString UserInfo::userId()
{
    return m_userId;
}

QString UserInfo::name()
{
    return m_name;
}

QString UserInfo::avatar()
{
    return m_avatar;
}

void UserInfo::setUserId(QString userId)
{
    m_userId=userId;
}

void UserInfo::setName(QString name)
{
    m_name=name;
}

void UserInfo::setAvatar(QString avatar)
{
    m_avatar=avatar;
}
