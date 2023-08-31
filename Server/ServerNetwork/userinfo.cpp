#include "userinfo.h"


UserInfo::UserInfo():
    userId(""),
    password(""),
    name(""),
    picture("")
{

}

UserInfo::UserInfo(
        QString _userId,
        QString _password,
        QString _name,
        QString _picture,
        QList<QString> _friendList,
        QList<QString> _groupList
        ):
    userId(_userId),
    password(_password),
    name(_name),
    picture(_picture),
    friendList(_friendList),
    groupList(_groupList)

{

}

UserInfo::UserInfo(const UserInfo &_userInfo):
    QObject(),
   userId(_userInfo.userId),
   password(_userInfo.password),
   name(_userInfo.name),
   picture(_userInfo.picture),
   friendList(_userInfo.friendList),
   groupList(_userInfo.groupList)


{

}

//QString UserInfo::toJson()
//{
//    QJsonObject userInfo;
//    userInfo["userId"] = userId;
//    userInfo["password"] = password;
//    userInfo["name"] = name;
////    userInfo["picture"] = picture;
////    userInfo["friendList"] = friendList;
////    userInfo["groupList"] = groupList;
//}
