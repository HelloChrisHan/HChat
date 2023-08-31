#ifndef USERINFO_H
#define USERINFO_H
#include <QString>
#include<QObject>
#include<QJsonObject>

/*
完成人：张兆熙，韩闯
*/
class UserInfo: public QObject
{
    Q_OBJECT
public:
    UserInfo();
    UserInfo(QString,QString,QString,QString,QList<QString>,QList<QString>);
    UserInfo(const UserInfo& _userInfo);
    QString userId;
    QString password;
    QString name;
    QString picture;
    QList<QString> friendList;
    QList<QString> groupList;
    QString toJson();
};

#endif // USERINFO_H
