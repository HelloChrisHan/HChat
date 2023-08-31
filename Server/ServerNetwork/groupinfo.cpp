#include "groupinfo.h"

GroupInfo::GroupInfo():
    groupId(""),
    ownerId(""),
    name(""),
    picture("")
{

}

//这里QObject怎么初始化也不知道
GroupInfo::GroupInfo(QString _groupId,
                     QString _ownerId,
                     QString _name,
                     QByteArray _picture
                     ):
                groupId(_groupId),
                ownerId(_ownerId),
                name(_name),
                picture(_picture)
{

}

GroupInfo::GroupInfo(const GroupInfo &_groupInfo):
    groupId(_groupInfo.groupId),
    ownerId(_groupInfo.ownerId),
    name(_groupInfo.name),
    picture(_groupInfo.picture)
{

}
