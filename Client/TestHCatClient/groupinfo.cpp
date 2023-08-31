#include "groupinfo.h"

GroupInfo::GroupInfo(QString groupId, QString name, QString avatar, QList<QString> members)
    :m_groupId(groupId),m_name(name),m_avatar(avatar),m_members(members)
{

}

QString GroupInfo::groupId()
{
    return m_groupId;
}

QString GroupInfo::name()
{
    return m_name;
}

QString GroupInfo::avatar()
{
    return m_avatar;
}

QList<QString> GroupInfo::members()
{
    return m_members;
}

void GroupInfo::setGroupId(QString groupId)
{
    m_groupId=groupId;
}

void GroupInfo::setName(QString name)
{
    m_name=name;
}

void GroupInfo::setAvatar(QString avatar)
{
    m_avatar=avatar;
}
