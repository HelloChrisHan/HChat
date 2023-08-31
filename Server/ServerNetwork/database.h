#ifndef DATABASE_H
#define DATABASE_H

#include <QString>
#include <QByteArray>
#include <iostream>
#include <QtSql/QSqlDatabase>

#include"userinfo.h"
#include"groupinfo.h"

/*
类定义完成人：张兆熙
*/
class DataDB
{
public:
    explicit DataDB();
    ~DataDB();

    // 娣诲姞濂藉弸
    void addFriend(QString userId1, QString userId2);

    // 鍔犲叆缇ょ粍
    void joinGroup(QString groupId, QString userId);

    // 鍒犻櫎濂藉弸
    void removeFriend(QString userId1, QString userId2);

    // 閫€鍑虹兢缁?
    void leaveGroup(QString groupId, QString userId);

    //娉ㄥ唽锛屾妸鏂扮殑鐢ㄦ埛鍜屽瘑鐮佸姞鍏ユ暟鎹簱
    void regist(QString userId, QString password, QString name, QString userIp);

    //妫€鏌ョ敤鎴峰悕鍜屽瘑鐮佹槸鍚︽纭?
    bool checkUserExistence(QString userId, QString password);

    //鏍规嵁浼犲叆鐨勭敤鎴峰悕鍜屽瘑鐮佽繑鍥炵敤鎴峰熀鏈俊鎭?
    UserInfo getUserInfo(QString userId);

    //妫€鏌ョ兢鑱婃槸鍚﹀瓨鍦?
    bool checkGroupExistence(QString groupId);

    //浼犲叆缇d, 瑙ｆ暎涓€涓兢
    void dismissGroup(QString groupId);

    //浼犲叆涓€涓敤鎴穒d锛岃繑鍥炰粬鎵€鏈夊ソ鍙嬬殑鍒楄〃
    QList<QString> getFriendsList(QString userId);

    //浼犲叆涓€涓敤鎴穒d锛岃繑鍥炲寘鍚墍鏈変粬鍔犲叆鐨勭兢鑱婄殑id鐨勫垪琛?
    QList<QString> getGroupsList(QString userId);

    //浼犲叆鐢ㄦ埛鍚嶅拰鏂扮殑瀵嗙爜锛屽湪鏁版嵁搴撲腑淇敼
    void changePassword(QString userId, QString newPassword);

    //鍒涘缓涓€涓兢缁勶紝缇よ亰淇℃伅鍖呮嫭锛氱兢涓汇€佺兢鍚嶇О銆佺兢澶村儚锛岀敓鎴愪竴涓兢id
    QString createGroup(QString ownerId, QString groupName, QByteArray picture);

    //杩斿洖缇よ亰鐨勫熀鏈俊鎭?
    GroupInfo getGroupInfo(QString groupId);

    //鍦ㄦ暟鎹簱涓姞鍏ヤ竴寮犲浘鐗囷紝杩斿洖鍥剧墖id
    QString addPicture(QByteArray picture);

    //浼犲叆缇d锛岃繑鍥炶缇ゆ墍鏈夋垚鍛樼粍鎴愮殑鍒楄〃
    QList<QString> getGroupMembers(QString groupId);

    //浼犲叆缇ゅ彿鍜屾柊鐨勭兢澶村儚锛屽苟淇敼鏁版嵁搴?
    void setGroupPicture(QString groupId, QByteArray picture);

    //浼犲叆缇ゅ彿鍜屾柊鐨勭兢鍚嶇О锛屽苟鍦ㄦ暟鎹簱涓慨鏀?
    void setGroupName(QString groupId, QString name);

    QString generateGroupId();

    QString generatePictureId();

    QString getIpAddress(QString userId);

    QString getMaxGroupId();

    QString getMaxPictureId();

    bool checkIsFriend(QString userId1, QString userId2);

    void offLine(QString userId);

    void login(QString userId, QString userIp);

    bool checkIdExist(QString userId);

    bool checkOnLine(QString userId);

    bool isFriend(QString userId1, QString userId2);

    void editUserAvatar(QString userId,QString picture);
    void editUserName(QString userId,QString name);

    bool checkInGroup(QString userId, QString groupId);
public:
    QSqlDatabase db;
};


#endif // DB_H








