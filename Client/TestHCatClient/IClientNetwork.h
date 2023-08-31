#ifndef ICLIENTNETWORK_H
#define ICLIENTNETWORK_H
#include<QObject>
#include<QImage>

class IClientNetwork: public QObject
{
    Q_OBJECT
public:
    virtual bool connectToServer() =0;
    virtual bool disConnect() =0;

    virtual void login(QString userId, QString pwd) =0;//done
    virtual void regist(QString userId, QString name, QString pwd) =0;//done
    virtual void changePwd(QString oldPwd,QString newPwd) =0;//todo done
    virtual void editAvatar(QImage avatar) =0;
    virtual void editName(QString name) =0;

    virtual void addFriend(QString userId) =0;//done
    virtual void removeFriend(QString userId) =0;

    virtual void joinGroup(QString groupId) =0;//todo done
    virtual void leaveGroup(QString groupId) =0;
    virtual void createGroup(QString groupName) =0;
    virtual void editGroupName(QString groupId, QString groupName) =0; //todo
    virtual void editGroupAvatar(QString goupId, QImage groupAvatar) =0; //todo
    virtual void dismissGroup(QString groupId) =0; //todo

    virtual void sendUserText(QString userId, QString text) =0;
    virtual void sendUserImage(QString userId, QImage image) =0; //todo done
    virtual void sendUserEmote(QString userId, QString emoteId) =0; //todo done

    virtual void sendGroupText(QString groupId, QString text) =0; //todo //done
    virtual void sendGroupImage(QString groupId, QImage image) =0; //todo //done
    virtual void sendGroupEmote(QString groupId, QString emoteId) =0; //todo //done


    virtual void requestFriendInfo(QString friendId,QString type) =0;
    virtual void requestGroupInfo(QString groupId) =0;

    virtual void createGroup(QString name, QImage image) = 0;

    virtual void sendUserSound(QString userId) =0;

signals:
    void loginSignal(bool isSuccess,QString name, QImage avatar, QList<QString> friendList, QList<QString> groupList);  //Done
    void registSignal(bool);

    void receiveFriendInfoSignal(QString name, QImage avatar, QString userId, QString type);                //Done
    void receiveGroupInfoSignal(QString name, QImage avatar, QString groupId, QList<QString> memberId);     //Done

    void receiveUserTextSignal(QString userId, QString textMsg);    //Done
    void receiveUserPictureSignal(QString userId, QImage imgMsg);   //Done
    void receiveUserEmoteSignal(QString userId, QString emoteMsg);  //Done

    void receiveGroupTextSignal(QString groupId, QString userId, QString textMsg);      //Done
    void receiveGroupPictureSignal(QString groupId, QString userId, QImage imgMsg);     //Done
    void receiveGroupEmoteSignal(QString groupId, QString userId, QString emoteMsg);    //Done

    void addedFriendSignal(QString name, QImage avatar, QString userId); //?







    //new
    void changePasswordSignal(bool isSuccess);
    void receiveUserPictureIdSignal(QString userId, QString pictureId);
    void receiveGroupPictureIdSignal(QString groupId, QString userId, QString pictureId);
    void joinGroupSignal(QString name, QImage avatar, QList<QString> membersList);
    void editGroupInfoSignal(QString groupId, QString name, QImage imgMsg);
    void dismissGroupSignal(QString groupId);
    void receivedSoundSignal();
};

#endif // ICLIENTNETWORK_H
