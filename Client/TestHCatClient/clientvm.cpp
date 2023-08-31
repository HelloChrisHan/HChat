#include "clientvm.h"
//#include "testnetwork.h"
#include<QTimer>
#include<QSound>

ClientVM::ClientVM(AvatarImageProvider* provider,IClientNetwork* network,QObject* parent)
    :avatarProvider(provider),network(network)
{
    network->connectToServer();
//    addMsg("11111",false);
//    addMsg("22222",false);
//    addMsg("333sdfsdfsdfsdfsdfsdf33",true);
//    network=new TestNetwork();

    m_lsFriend.append(new Chat("Welcome","-1"));
//    m_lsFriend.append(new Chat("Friend2","-2"));
    m_lsGroup.append(new Chat("Welcome","-1"));
//    m_lsGroup.append(new Chat("Group2","-2"));

    friendMsg["-1"] = QList<Message*>();
    friendMsg["-1"].append(new Message(false,"","Assistant","text","Welcome to HChat!"));
//    friendMsg["-1"].append(new Message(true,"","Me","text","reply friend 1"));
//    friendMsg["-1"].append(new Message(true,"","Me","emote","","1.jpg"));
//    friendMsg["-1"].append(new Message(false,"","Friend","emote","","2.jpg"));
//    friendMsg["-2"] = QList<Message*>();
//    friendMsg["-2"].append(new Message(false,"","Friend","text","from friend 2"));
//    friendMsg["-2"].append(new Message(true,"","Me","text","reply friend 2"));

    groupMsg["-1"] = QList<Message*>();
    groupMsg["-1"].append(new Message(false,"","Assistant","text","Welcome to HChat!"));
//    groupMsg["-1"].append(new Message(true,"","Me","text","reply group 1"));
//    groupMsg["-2"] = QList<Message*>();
//    groupMsg["-2"].append(new Message(false,"","Friend","text","from group 2"));
//    groupMsg["-2"].append(new Message(true,"","Me","text","reply group 2"));


    emit lsFriendChanged();
    m_lsMsg = &friendMsg["-1"];
    emit lsMsgChanged();
    m_chatName=m_lsFriend[0]->name();
    m_chatType="friend";
    m_chatId=m_lsFriend[0]->id();
    m_chatAvatar=m_lsFriend[0]->avatar();

//    m_lsChat.append(new Chat("Friend1"));
//    m_lsChat.append(new Chat("Friend2"));

//    m_lsChat[1]->addMsg("From friend1",false);
//    m_lsChat[1]->addMsg("Reply friend1",true);
//    m_lsChat[2]->addMsg("From friend2",false);
//    m_lsChat[2]->addMsg("Reply friend2",true);
//    m_chat=m_lsChat[0];

//    client = new ClientSocket();
//    connect(
//        client,
//        &ClientSocket::receivedMessage,
//        [&](QString msg)
//        {
//            addMsg(msg,false);
//        }
//    );
    connect(
        network,
        &IClientNetwork::receiveUserTextSignal,
        [&](QString userId, QString textMsg){
            addMsg(
                "friend",
                userId,
                false,
                m_userInfo[userId].avatar(),
                m_userInfo[userId].name(),
                "text",
                textMsg
            );
        }
    );
    connect(
        network,
        &IClientNetwork::receiveUserEmoteSignal,
        [&](QString userId, QString emoteMsg){
            qDebug()<<"emote!!!!!";
            addMsg(
                "friend",
                userId,
                false,
                m_userInfo[userId].avatar(),
                m_userInfo[userId].name(),
                "emote",
                emoteMsg
            );
        }
    );
    connect(
        network,
        &IClientNetwork::receiveGroupTextSignal,
        [&](QString groupId, QString userId, QString textMsg){
            addMsg(
                "group",
                groupId,
                false,
                m_userInfo[userId].avatar(),
                m_userInfo[userId].name(),
                "text",
                textMsg
            );
        }
    );
    connect(
        network,
        &IClientNetwork::receiveGroupEmoteSignal,
        [&](QString groupId, QString userId, QString emoteMsg){
            addMsg(
                "group",
                groupId,
                false,
                m_userInfo[userId].avatar(),
                m_userInfo[userId].name(),
                "emote",
                emoteMsg
            );
        }
    );
    connect(
        network,
        &IClientNetwork::loginSignal,
        this,
        &ClientVM::afterLogin
    );
//    connect(
//        this,
//        &ClientVM::loginSuccess,
//        [&](QList<QString> friendList, QList<QString> groupList){
//            for(int i=0;i<friendList.size();i++){
//                network->requestFriendInfo(friendList[i],"friend");
//            }
//            for(int i=0;i<groupList.size();i++){
//                network->requestGroupInfo(groupList[i]);
//            }
//        }
//    );
    connect(
        network,
        &IClientNetwork::receiveFriendInfoSignal,
        [&](QString name, QImage avatar, QString userId, QString type){
            avatarProvider->addImage("user:"+userId,avatar);
            m_userInfo[userId]=UserInfo(userId,name,userId);
            if(type=="friend"){
                bool exist=false;
                int ind;

                for(int i=0;i<m_lsFriend.size();i++){
                    if(userId==m_lsFriend[i]->id()){
                        exist=true;
                        ind=i;
                        break;
                    }
                }

                if(!exist){
                    m_lsFriend.push_front(
                        new Chat(name, userId, "user:"+userId)
                        );
                    friendMsg[userId]=QList<Message*>();
                }
                else{

                }
                qDebug()<<name;
                emit lsFriendChanged();
            }
        }
    );
    connect(
        network,
        &IClientNetwork::receiveGroupInfoSignal,
        this,
        &ClientVM::afterReceiveGroupInfo
    );
    connect(
        network,
        &IClientNetwork::receivedSoundSignal,
        [&](){
            QSound::play(":/sounds/yeah.wav");
        }
    );
}

QQmlListProperty<Message> ClientVM::lsMsg()
{
    return QQmlListProperty<Message>(this,*m_lsMsg);
}

void ClientVM::addMsg(
        QString chatType,
        QString chatId,
        bool isSelf,
        QString avatar,
        QString name,
        QString type,
        QString content
        )
{
//    m_lsMsg->push_front(new Message(isSelf,"","Me","text",msg));
//    emit lsMsgChanged();

    if(chatType=="friend"){
        if(type=="text"){
            friendMsg[chatId].push_front(
                new Message(
                    isSelf,
                    avatar,
                    name,
                    type,
                    content
                )
            );
        }
        else if(type=="emote"){
            friendMsg[chatId].push_front(
                new Message(
                    isSelf,
                    avatar,
                    name,
                    type,
                    "",
                    content
                )
            );
        }
        else if(type=="image"){
            friendMsg[chatId].push_front(
                new Message(
                    isSelf,
                    avatar,
                    name,
                    type,
                    "",
                    "",
                    content
                )
            );
        }
        if(m_lsMsg==&friendMsg[chatId]){
            emit lsMsgChanged();
        }
    }
    else if(chatType=="group"){
        if(type=="text"){
            groupMsg[chatId].push_front(
                new Message(
                    isSelf,
                    avatar,
                    name,
                    type,
                    content
                )
            );
        }
        else if(type=="emote"){
            groupMsg[chatId].push_front(
                new Message(
                    isSelf,
                    avatar,
                    name,
                    type,
                    "",
                    content
                )
            );
        }
        else if(type=="image"){
            groupMsg[chatId].push_front(
                new Message(
                    isSelf,
                    avatar,
                    name,
                    type,
                    "",
                    "",
                    content
                )
            );
        }
        if(m_lsMsg==&groupMsg[chatId]){
            emit lsMsgChanged();
        }
    }
}

QString ClientVM::chatType()
{
    return m_chatType;
}

QQmlListProperty<Chat> ClientVM::lsFriend()
{
    return QQmlListProperty<Chat>(this,m_lsFriend);
}

QQmlListProperty<Chat> ClientVM::lsGroup()
{
    return QQmlListProperty<Chat>(this,m_lsGroup);
}

QString ClientVM::chatName()
{
    return m_chatName;
}

QString ClientVM::chatId()
{
    return m_chatId;
}

QString ClientVM::chatAvatar()
{
    return m_chatAvatar;
}

void ClientVM::sendMessage(QString msg)
{
//    addMsg(msg,true);
    addMsg(
        m_chatType,
        m_chatId,
        true,
        m_myInfo.avatar(),
        m_myInfo.name(),
        "text",
        msg
    );
    if(network!=nullptr)
    {
        if(m_chatType=="friend"){
            network->sendUserText(m_chatId,msg);
        }
        else if(m_chatType=="group"){
            network->sendGroupText(m_chatId,msg);
        }
    }
}

void ClientVM::sendEmote(QString msg)
{
    addMsg(
        m_chatType,
        m_chatId,
        true,
        m_myInfo.avatar(),
        m_myInfo.name(),
        "emote",
        msg
    );
    if(network!=nullptr){
        if(m_chatType=="friend"){
            network->sendUserEmote(m_chatId,msg);
        }
        else if(m_chatType=="group"){
            network->sendGroupEmote(m_chatId,msg);
        }
    }
}

void ClientVM::login(QString userId, QString pwd)
{
    m_myInfo.setUserId(userId);
    if(network!=nullptr){
        network->login(userId, pwd);
        qDebug()<<"login";
    }
}

void ClientVM::regist(QString userId, QString name, QString pwd)
{
    if(network!=nullptr){
        network->regist(userId, name, pwd);
        qDebug()<<"register";
    }
}

void ClientVM::selectChat(QString chatId, QString name, QString avatar)
{
    if(m_chatType=="friend"){
        m_lsMsg=&friendMsg[chatId];
    }
    else if(m_chatType=="group"){
        m_lsMsg=&groupMsg[chatId];
    }
    m_chatName=name;
    m_chatId=chatId;
    m_chatAvatar=avatar;
    emit chatNameChanged();
    emit lsMsgChanged();
    emit chatIdChanged();
    emit chatAvatarChanged();
}

void ClientVM::addFriend(QString id)
{
    if(network!=nullptr)
        network->addFriend(id);
}

void ClientVM::addGroup(QString id)
{
    if(network!=nullptr)
        network->joinGroup(id);
}

void ClientVM::logOut()
{
    network->disConnect();
}

void ClientVM::createGroup(QString id)
{
    network->createGroup(id);
}

void ClientVM::changeAvatar(QString location)
{
    qDebug()<<"avatar url: "<<location;

    QImage avatar;
    qDebug()<<avatar.load(QUrl(location).toLocalFile())<<"||||||||||||||||||||||";
    network->editAvatar(avatar);
}

void ClientVM::changeName(QString name)
{
    network->editName(name);
}

void ClientVM::removeFriend(int i)
{
    QString removeUserId = m_lsFriend[i]->id();
    if(removeUserId=="-1"){
        return;
    }
    m_lsFriend.removeAt(i);
    m_chatName=m_lsFriend[0]->name();
    m_chatType="friend";
    m_chatId=m_lsFriend[0]->id();
    m_chatAvatar=m_lsFriend[0]->avatar();
    emit chatTypeChanged();
    emit chatNameChanged();
    emit chatIdChanged();
    emit chatAvatarChanged();
    emit lsFriendChanged();
    network->removeFriend(removeUserId);
}

void ClientVM::leaveGroup(int i)
{
    QString leaveGroupId = m_lsGroup[i]->id();
    if(leaveGroupId=="-1"){
        return;
    }
    m_lsGroup.removeAt(i);
    m_chatName=m_lsGroup[0]->name();
    m_chatType="group";
    m_chatId=m_lsGroup[0]->id();
    m_chatAvatar=m_lsGroup[0]->avatar();
    emit chatTypeChanged();
    emit chatNameChanged();
    emit chatIdChanged();
    emit chatAvatarChanged();
    emit lsFriendChanged();
    network->leaveGroup(leaveGroupId);
}

void ClientVM::sendSound()
{
//    QSound::play(":/sounds/yeah.wav");
    if(m_chatType=="friend"){
        network->sendUserSound(m_chatId);
    }
    else if(m_chatType=="group"){

    }
}

void ClientVM::playMusic()
{
    QSound::play(":/sounds/music.wav");
}

void ClientVM::setChatType(QString type)
{
    if(type == m_chatType)
        return;
    m_chatType=type;
    emit chatTypeChanged();
}

void ClientVM::afterLogin(bool isSuccess, QString name, QImage avatar, QList<QString> friendList, QList<QString> groupList)
{
    m_myInfo.setName(name);
    avatarProvider->addImage("user:"+m_myInfo.userId(),avatar);
    m_myInfo.setAvatar(m_myInfo.userId());
    for(int i=0;i<friendList.size();i++){
//        network->requestFriendInfo(friendList[i],"friend");
//        qDebug()<<"current: "<<i;
        QTimer::singleShot(
            500*(i+2),
            [=]{
                network->requestFriendInfo(friendList[i],"friend");
            }
        );
    }

//    qDebug()<<groupList.size()<<" <-----groups!!";

    for(int i=0;i<groupList.size();i++){
//        network->requestGroupInfo(groupList[i]);
        QTimer::singleShot(
            500*(friendList.size()+i+3),
            [=]{
                network->requestGroupInfo(groupList[i]);
            }
        );
    }
}

void ClientVM::afterReceiveGroupInfo(QString name, QImage avatar, QString groupId, QList<QString> memberId)
{
    avatarProvider->addImage("group:"+groupId,avatar);
    m_groupInfo[groupId]=GroupInfo(groupId,name,"group:"+groupId,memberId);
    bool exist=false;
    int ind;
    for(int i=0;i<m_lsGroup.size();i++){
        if(groupId==m_lsGroup[i]->id()){
            exist=true;
            ind=i;
            break;
        }
    }
    if(!exist){
        m_lsGroup.push_front(
            new Chat(name, groupId, "group:"+groupId)
        );
        groupMsg[groupId]=QList<Message*>();
    }
    else{
        m_lsGroup[ind]->name()=name;
    }
//    qDebug()<<"-------------------";
    emit lsGroupChanged();
    for(int i=0;i<memberId.size();i++){
        QTimer::singleShot(
            500*i,
            [=]{
                network->requestFriendInfo(memberId[i],"group");
            }
        );
    }
}

