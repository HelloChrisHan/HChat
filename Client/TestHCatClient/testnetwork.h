#ifndef TESTNETWORK_H
#define TESTNETWORK_H

#include "IClientNetwork.h"
#include <QObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QImage>
#include <QByteArray>
#include <QTcpSocket>

#include"groupinfo.h"

class TestNetwork: public IClientNetwork
{
    Q_OBJECT
public:
    TestNetwork(QObject *parent=nullptr);
    QString UserId;
    QTcpSocket *socket;
    bool connectToServer() override;
    bool disConnect() override;

    void login(QString userId, QString pwd) override;
    void regist(QString userId, QString name, QString pwd) override;
    void changePwd(QString oldPwd, QString newPwd) override;

    void addFriend(QString userId) override;
    void removeFriend(QString userId) override;

    void joinGroup(QString groupId) override;
    void leaveGroup(QString groupId) override;
    void createGroup(QString groupName) override;
    void editGroupName(QString groupId, QString groupName) override;
    void editGroupAvatar(QString groupId, QImage groupAvatar) override;
    void dismissGroup(QString groupId) override;

    void sendUserText(QString userId, QString text) override;
    void sendUserImage(QString userId, QImage image) override;
    void sendUserEmote(QString userId, QString emoteId) override;

    void sendGroupText(QString groupId, QString text) override;
    void sendGroupImage(QString groupId, QImage image) override;
    void sendGroupEmote(QString groupId, QString emoteId) override;

    void createGroup(QString name, QImage image) override;

//    void sendUserTextSignal();
//    void sendUserPictureSignal();
//    void sendUserEmoteSignal();

//    void sendGroupTextSignal();
//    void sendGroupPictureSignal();
//    void sendGroupEmoteSignal();
//signals:
//    void receiveUserTextSignal(QString friendId, QString userId, QString userName, QString textMsg);
//    void receiveUserPictureSignal(QString friendId, QString userId, QString userName, QImage imgMsg);
//    void receiveUserEmoteSignal(QString friendId, QString userId, QString userName, QString emoteMsg);

//    void receiveGroupTextSignal(QString groupId, QString userId, QString userName, QString textMsg);
//    void receiveGroupPictureSignal(QString groupId, QString userId, QString userName, QImage imgMsg);
//    void receiveGroupEmoteSignal(QString groupId, QString userId, QString userName, QString emoteMsg);

    // IClientNetwork interface
public:
    void requestFriendInfo(QString friendId, QString type) override;
    void requestGroupInfo(QString groupId) override;

    // IClientNetwork interface
public:
    void editAvatar(QImage avatar) override;
    void editName(QString name) override;
    void sendUserSound(QString userId) override;
};

#endif // TESTNETWORK_H
