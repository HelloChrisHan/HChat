#ifndef SERVERVIEWMODEL_H
#define SERVERVIEWMODEL_H
#include<QTcpServer>
#include<QObject>
#include<QByteArray>
#include<QJsonArray>
#include<QJsonObject>
#include<QtSql/QSqlDatabase>

#include "iservernetwork.h"
#include "message.h"
#include"database.h"

/*
完成人：张兆熙
*/
class ServerViewModel:public QObject
{
    Q_OBJECT
public:
    ServerViewModel(IServerNetwork* serverNetwork=nullptr);
    IServerNetwork* network;
    DataDB* database;

    bool receiveMessage(Message msg);
    bool sendMessage(Message msg, QList<QString> receiverList);
    bool login(Message msg);
    bool regist(Message msg);
    bool changePassword(Message msg);
    bool addFriend(Message msg);
    bool joinGroup(Message msg);
    bool removeFriend(Message msg);
    bool leaveGroup(Message msg);
    bool dealText(Message msg);
    bool dealPicture(Message msg);
    bool dealEmot(Message msg);                      //////////////////////
    bool editGroupInfo(Message msg);
    bool createGroup(Message msg);

    bool dismissGroup(Message msg);
    bool requestFriendInfo(Message msg);
    bool requestGroupInfo(Message msg);

    bool editUserInfo(Message msg);

    bool sendUserSound(Message msg);

    bool disConnect(Message msg);
    QByteArray compressPicture(QByteArray pic);
    QJsonObject conbineUserInfoIntoJson(UserInfo userInfo);
    QJsonObject conbineGroupInfoIntoJson(GroupInfo groupInfo);
};

#endif // SERVERVIEWMODEL_H
