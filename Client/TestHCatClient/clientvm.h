#ifndef CLIENTVM_H
#define CLIENTVM_H
#include<QObject>
#include<QtQuick>
#include<QMetaObject>
#include<QHash>
#include"message.h"
#include"clientsocket.h"
#include"IClientNetwork.h"
#include"chat.h"
#include"avatarimageprovider.h"
#include"userinfo.h"
#include"groupinfo.h"

class ClientVM:public QObject
{
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<Message> lsMsg READ lsMsg NOTIFY lsMsgChanged)
    Q_PROPERTY(QString chatType READ chatType WRITE setChatType NOTIFY chatTypeChanged)
    Q_PROPERTY(QQmlListProperty<Chat> lsFriend READ lsFriend NOTIFY lsFriendChanged)
    Q_PROPERTY(QQmlListProperty<Chat> lsGroup READ lsGroup NOTIFY lsGroupChanged)
    Q_PROPERTY(QString chatName READ chatName NOTIFY chatNameChanged)
    Q_PROPERTY(QString chatId READ chatId NOTIFY chatIdChanged)
    Q_PROPERTY(QString chatAvatar READ chatAvatar NOTIFY chatAvatarChanged)
//    Q_PROPERTY(bool isLogin READ isLogin NOTIFY loginChanged)

//    Q_PROPERTY(QQmlListProperty<Chat> lsChat READ lsChat NOTIFY lsChatChanged)
//    Q_PROPERTY(Chat chat READ chat NOTIFY chatChanged)
public:
    ClientVM(AvatarImageProvider*, IClientNetwork*, QObject* parent=nullptr);

    QQmlListProperty<Message> lsMsg();

    QString chatType();
    QString chatName();
    QString chatId();
    QString chatAvatar();

    QQmlListProperty<Chat> lsFriend();
    QQmlListProperty<Chat> lsGroup();




    void addMsg(
        QString chatType,
        QString chatId,
        bool isSelf,
        QString avatar,
        QString name,
        QString type,
        QString content
    );

//    Chat chat();
//    QQmlListProperty<Chat> lsChat();

    Q_INVOKABLE void sendMessage(QString);
//    Q_INVOKABLE void sendImage(QImage);     //TODO
    Q_INVOKABLE void sendEmote(QString);
    Q_INVOKABLE void login(QString,QString);
    Q_INVOKABLE void regist(QString,QString,QString);
    Q_INVOKABLE void selectChat(QString,QString,QString);
    Q_INVOKABLE void addFriend(QString);
    Q_INVOKABLE void addGroup(QString);
    Q_INVOKABLE void logOut();
    Q_INVOKABLE void createGroup(QString);
    Q_INVOKABLE void changeAvatar(QString);
    Q_INVOKABLE void changeName(QString);
    Q_INVOKABLE void removeFriend(int);
    Q_INVOKABLE void leaveGroup(int);
    Q_INVOKABLE void sendSound();
    Q_INVOKABLE void playMusic();


public slots:
    void setChatType(QString);

signals:
    void lsMsgChanged();
    void lsFriendChanged();
    void lsGroupChanged();
    void chatTypeChanged();
    void chatNameChanged();
    void chatIdChanged();
    void chatAvatarChanged();
//    void lsChatChanged();
//    void chatChanged();

private:
    void afterLogin(bool isSuccess, QString name, QImage avatar, QList<QString> friendList, QList<QString> groupList);
    void afterReceiveGroupInfo(QString name, QImage avatar, QString groupId, QList<QString> memberId);

private:
    QList<Message*> *m_lsMsg;
    QHash<QString,QList<Message*> > friendMsg;
    QHash<QString,QList<Message*> > groupMsg;
    QList<Chat*> m_lsFriend;
    QList<Chat*> m_lsGroup;

    QHash<QString,GroupInfo> m_groupInfo;
    QHash<QString,UserInfo> m_userInfo;
    UserInfo m_myInfo;


    QString m_chatType;
    QString m_chatId;
    QString m_chatName;
    QString m_chatAvatar;
//    Chat* m_chat;
//    QList<Chat*> m_lsChat;

//    ClientSocket* client;
    AvatarImageProvider* avatarProvider;
    IClientNetwork* network;

};

#endif // CLIENTVM_H
