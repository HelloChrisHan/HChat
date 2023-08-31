#include "database.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

//DataDB::DataDB():db(QSqlDatabase::addDatabase("QSQLITE"))
//{
//    // 创建SQLite数据库连接
////    db = QSqlDatabase::addDatabase("QSQLITE");
//    db.setDatabaseName("mydatabase.db");

//    if (!db.open()) {
//        qDebug() << "无法打开数据库连接: " << db.lastError().text();
//        return;
//    }

//    // 创建用户信息表
//    QSqlQuery query;
//    if (!query.exec("DROP TABLE IF EXISTS UserInfo") or
//            !query.exec("CREATE TABLE IF NOT EXISTS UserInfo (userId TEXT PRIMARY KEY, password TEXT, name TEXT, picture BLOB)") or
//            !query.exec("INSERT INTO UserInfo (userId, password, name) VALUES (\"0000\", \"0000\", \"test1\"), (\"0001\", \"0001\", \"test2\")")) {
//        qDebug() << "无法创建用户信息表: " << query.lastError().text();
//    }

//    // 创建好友关系表
//    if (!query.exec("DROP TABLE IF EXISTS Friend") or
//            !query.exec("CREATE TABLE IF NOT EXISTS Friend (userId1 TEXT, userId2 TEXT)") or
//            !query.exec("INSERT INTO Friend(userId1, userId2) VALUES(\"0000\",\"0001\")") or
//            !query.exec("INSERT INTO Friend(userId1, userId2) VALUES(\"0001\",\"0000\")")) {
//        qDebug() << "无法创建好友关系表: " << query.lastError().text();
//    }

//    // 创建群组表
//    //Recently Fixed - zzx, 8.28
//    if (!query.exec("CREATE TABLE IF NOT EXISTS GroupInfo (groupId TEXT, userId TEXT)"))) {
//        qDebug() << "无法创建群组表: " << query.lastError().text();
//    }

//    // 创建图片信息表
//    //Recently Fixed - zzx, 8.28
//    if (!query.exec("DROP TABLE IF EXISTS PictureInfo") or!query.exec("CREATE TABLE IF NOT EXISTS PictureInfo (pictureId TEXT PRIMARY KEY, picture BLOB)") or !query.exec("INSERT INTO PictureInfo (pictureId, picture) VALUES (\"00000\",\"000000\")")) {
//        qDebug() << "无法创建图片信息表: " << query.lastError().text();
//    }

//    if (!query.exec("DROP TABLE IF EXISTS UserIp") or!query.exec("CREATE TABLE UserIp (userId VARCHAR(255) PRIMARY KEY, ipAddress VARCHAR(255));")) {
//        qDebug() << "无法创建ip信息表: " << query.lastError().text();
//    }

//}


DataDB::DataDB():db(QSqlDatabase::addDatabase("QSQLITE"))
{
    // 创建SQLite数据库连接
//    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("mydatabase.db");

    if (!db.open()) {
        qDebug() << "无法打开数据库连接: " << db.lastError().text();
        return;
    }

    // 创建用户信息表
    QSqlQuery query;

//    query.exec("DROP TABLE IF EXISTS Friend");
//    query.exec("DROP TABLE IF EXISTS UserInfo");
//    query.exec("DROP TABLE IF EXISTS GroupInfo");
//    query.exec("DROP TABLE IF EXISTS PictureInfo");
//    query.exec("DROP TABLE IF EXISTS UserIp");
//    query.exec("DROP TABLE IF EXISTS GroupMembers");
//    query.exec("DROP TABLE IF EXISTS GroupInfo");

    if (!query.exec("CREATE TABLE IF NOT EXISTS UserInfo (userId TEXT PRIMARY KEY, password TEXT, name TEXT, picture TEXT)")) {
        qDebug() << "无法创建用户信息表: " << query.lastError().text();
    }

    // 创建好友关系表
    if (!query.exec("CREATE TABLE IF NOT EXISTS Friend (userId1 TEXT, userId2 TEXT)")) {
        qDebug() << "无法创建好友关系表: " << query.lastError().text();
    }
    // !query.exec("DROP TABLE IF EXISTS Friend") or 用于清除好友关系
    // 创建群组表
    //Recently Fixed - zzx, 8.28
    if (!query.exec("CREATE TABLE IF NOT EXISTS GroupInfo (groupId TEXT, ownerId TEXT, groupName TEXT, picture TEXT)") or!query.exec("INSERT INTO GroupInfo (groupId) VALUES (\"0\")"  )) {
        qDebug() << "无法创建群组表: " << query.lastError().text();
    }

    // 创建图片信息表
    //Recently Fixed - zzx, 8.28
    if (!query.exec("DROP TABLE IF EXISTS PictureInfo") or!query.exec("CREATE TABLE IF NOT EXISTS PictureInfo (pictureId TEXT PRIMARY KEY, picture BLOB)") or !query.exec("INSERT INTO PictureInfo (pictureId, picture) VALUES (\"00000\",\"000000\")")) {
        qDebug() << "无法创建图片信息表: " << query.lastError().text();
    }

    if (!query.exec("DROP TABLE IF EXISTS UserIp") or!query.exec("CREATE TABLE IF NOT EXISTS UserIp (userId VARCHAR(255) PRIMARY KEY, ipAddress VARCHAR(255));")) {
        qDebug() << "无法创建ip信息表: " << query.lastError().text();
    }

    if (!query.exec("CREATE TABLE IF NOT EXISTS GroupMembers (groupId TEXT, userId TEXT)")){
        qDebug()<<"无法创建群成员表";
    }
}


void DataDB::addFriend(QString userId1, QString userId2)
{
    QSqlQuery query;
    query.prepare("INSERT INTO Friend (userId1, userId2) VALUES (?, ?)");
    query.addBindValue(userId1);
    query.addBindValue(userId2);
    qDebug() << "数据库文件创建成功";

    if (!query.exec()) {
        qDebug() << "好友添加失败: " << query.lastError().text();
    } else {
        qDebug() << "好友添加成功";
    }
}

void DataDB::joinGroup(QString groupId, QString userId)
{
    QSqlQuery query;
    query.prepare("INSERT INTO GroupMembers (groupId, userId) VALUES (?, ?)");
    query.addBindValue(groupId);
    query.addBindValue(userId);

    if (!query.exec()) {
        qDebug() << "加入群组失败: " << query.lastError().text();
    } else {
        qDebug() << "加入群组成功";
    }
}

void DataDB::removeFriend(QString userId1, QString userId2)
{
    QSqlQuery query;
    query.prepare("DELETE FROM Friend WHERE (userId1 = ? AND userId2 = ?) OR (userId1 = ? AND userId2 = ?)");
    query.addBindValue(userId1);
    query.addBindValue(userId2);
    query.addBindValue(userId2);
    query.addBindValue(userId1);

    if (!query.exec()) {
        qDebug() << "好友删除失败: " << query.lastError().text();
    } else {
        qDebug() << "好友删除成功";
    }
}

void DataDB::leaveGroup(QString groupId, QString userId)
{
    QSqlQuery query;
    query.prepare("DELETE FROM GroupMembers WHERE groupId = ? AND userId = ?");
    query.addBindValue(groupId);
    query.addBindValue(userId);

    if (!query.exec()) {
        qDebug() << "退出群组失败: " << query.lastError().text();
    } else {
        qDebug() << "退出群组成功";
    }
}

void DataDB::regist(QString userId, QString password, QString name, QString userIp)
{
    QSqlQuery query;
    query.prepare("INSERT INTO UserInfo (userId, password, name) VALUES (?, ?, ?)");
    query.addBindValue(userId);
    query.addBindValue(password);
    query.addBindValue(name);
//    query.addBindValue(userIp);

    if (!query.exec()) {
        qDebug() << "注册失败: " << query.lastError().text();
    } else {
        qDebug() << "注册成功";
    }
}

bool DataDB::checkUserExistence(QString userId, QString password)
{
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM UserInfo WHERE userId = ? AND password = ?");
    query.addBindValue(userId);
    query.addBindValue(password);

    if (!query.exec()) {
        qDebug() << "查询用户失败: " << query.lastError().text();
        return false;
    }

    if (query.next()) {
        int count = query.value(0).toInt();
        return count > 0;
    }

    return false;
}

UserInfo DataDB::getUserInfo(QString userId)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM UserInfo WHERE userId = ?");
    query.addBindValue(userId);
    qDebug()<<userId<<"FUCK";
    if (!query.exec()) {
        qDebug() << "获取用户信息失败: " << query.lastError().text();
        return UserInfo();
    }

    if (query.next()) {
//        QString userId = query.value("userId").toString();
        QString password = query.value("password").toString();
        QString name = query.value("name").toString();
        QByteArray picture = query.value("picture").toByteArray();

        /**
         * 在这里修改了三行，使其满足构造函数
         */
        QList<QString> friendsList = getFriendsList(userId);
        QList<QString> groupsList = getGroupsList(userId);
        qDebug()<<"UID"<<userId;
        qDebug()<<"LOGIN: "<<groupsList.size()<<" <-----groupSIZE!";
        return UserInfo(userId, password, name, picture, friendsList,groupsList);
    }
    qDebug()<<"failfailfailfail";

    return UserInfo();
}

bool DataDB::checkGroupExistence(QString groupId)
{
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM GroupInfo WHERE groupId = ?");
    query.addBindValue(groupId);

    if (!query.exec()) {
        qDebug() << "查询群聊失败: " << query.lastError().text();
        return false;
    }

    if (query.next()) {
        int count = query.value(0).toInt();
        return count > 0;
    }

    return false;
}

void DataDB::dismissGroup(QString groupId)
{
    QSqlQuery query;
    query.prepare("DELETE FROM GroupMembers WHERE groupId = ?");
    query.addBindValue(groupId);
    if(query.exec())
    {
        query.prepare("DELETE FROM GroupInfo WHERE groupId = ?");
        query.addBindValue(groupId);

        if (!query.exec()) {
            qDebug() << "解散群聊失败: " << query.lastError().text();
        } else {
            qDebug() << "解散群聊成功";
        }

    }


}

QList<QString> DataDB::getFriendsList(QString userId)
{
    QList<QString> friendsList;

    QSqlQuery query;
    query.prepare("SELECT userId2 FROM Friend WHERE userId1 = ?");
    query.addBindValue(userId);

    if (!query.exec()) {
        qDebug() << "获取好友列表失败: " << query.lastError().text();
        return friendsList;
    }

    while (query.next()) {
        QString friendId = query.value("userId2").toString();
        friendsList.append(friendId);
    }

    return friendsList;
}

QList<QString> DataDB::getGroupsList(QString userId)
{
    QList<QString> groupsList;

    QSqlQuery query;
    query.prepare("SELECT groupId FROM GroupMembers WHERE userId = ?");
    query.addBindValue(userId);

    if (!query.exec()) {
        qDebug() << "获取群聊列表失败: " << query.lastError().text();
        return groupsList;
    }

    while (query.next()) {
        qDebug()<<"^^^^";
        QString groupId = query.value("groupId").toString();
        groupsList.append(groupId);
    }

    return groupsList;
}


void DataDB::changePassword(QString userId, QString newPassword)
{
    QSqlQuery query;
    query.prepare("UPDATE UserInfo SET password = ? WHERE userId = ?");
    query.addBindValue(newPassword);
    query.addBindValue(userId);

    if (!query.exec()) {
        qDebug() << "修改密码失败: " << query.lastError().text();
    } else {
        qDebug() << "密码修改成功";
    }
}

QString DataDB::createGroup(QString ownerId, QString groupName, QByteArray picture)
{
    QString groupId = generateGroupId(); // 生成群ID的函数，具体实现根据需求自行定义
    QSqlQuery query;
    query.prepare("INSERT INTO GroupInfo (groupId, ownerId, groupName, picture) VALUES (?, ?, ?, ?)");
    query.addBindValue(groupId);
    query.addBindValue(ownerId);
    query.addBindValue(groupName);
    query.addBindValue(picture);


    if (!query.exec()) {
        qDebug() << "创建群聊失败: " << query.lastError().text();
        return QString();
    }


    query.prepare("INSERT INTO GroupMembers (groupId, userId) VALUES (?, ?)");
    query.addBindValue(groupId);
    query.addBindValue(ownerId);

    if(!query.exec()){
        qDebug()<<"创建第一个成员失败" << query.lastError().text();
        return QString();
    }

    qDebug() << "群聊创建成功，群ID: " << groupId;
    return groupId;
}

GroupInfo DataDB::getGroupInfo(QString groupId)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM GroupInfo WHERE groupId = ?");
    query.addBindValue(groupId);

    if (!query.exec()) {
        qDebug() << "获取群聊信息失败: " << query.lastError().text();
        return GroupInfo();
    }

    if (query.next()) {
        QString groupId = query.value("groupId").toString();
        QString ownerId = query.value("ownerId").toString();
        QString groupName = query.value("groupName").toString();
        QByteArray picture = query.value("picture").toByteArray();

        return GroupInfo(groupId, ownerId, groupName, picture);
    }

    return GroupInfo();
}

QString DataDB::addPicture(QByteArray picture)
{
    QString pictureId = generatePictureId(); // 生成图片ID的函数，具体实现根据需求自行定义

    QSqlQuery query;
    query.prepare("INSERT INTO Pictures (pictureId, picture) VALUES (?, ?)");
    query.addBindValue(pictureId);
    query.addBindValue(picture);

    if (!query.exec()) {
        qDebug() << "添加图片失败: " << query.lastError().text();
        return QString();
    }

    qDebug() << "图片添加成功，图片ID: " << pictureId;
    return pictureId;
}

QList<QString> DataDB::getGroupMembers(QString groupId)
{
    QList<QString> membersList;

    QSqlQuery query;
    query.prepare("SELECT userId FROM GroupMembers WHERE groupId = ?");
    query.addBindValue(groupId);

    if (!query.exec()) {
        qDebug() << "获取群成员列表失败: " << query.lastError().text();
        return membersList;
    }

    while (query.next()) {
        QString memberId = query.value("userId").toString();
        membersList.append(memberId);
    }

    return membersList;
}

void DataDB::setGroupPicture(QString groupId, QByteArray newPicture)
{
    QSqlQuery query;
    query.prepare("UPDATE groupInfo SET picture = ? WHERE groupId = ?");
    query.addBindValue(newPicture);
    query.addBindValue(groupId);

    if (!query.exec()) {
        qDebug() << "修改群头像失败: " << query.lastError().text();
    } else {
        qDebug() << "群头像修改成功";
    }
}

void DataDB::setGroupName(QString groupId, QString newName)
{
    QSqlQuery query;
    query.prepare("UPDATE groupInfo SET groupName = ? WHERE groupId = ?");
    query.addBindValue(newName);
    query.addBindValue(groupId);

    if (!query.exec()) {
        qDebug() << "修改群名称失败: " << query.lastError().text();
    } else {
        qDebug() << "群名称修改成功";
    }
}

QString DataDB::generateGroupId()
{
    QString maxId = getMaxGroupId();
    QString newId = QString::number(maxId.toUInt() + 1);
    return newId;
}

QString DataDB::generatePictureId()
{
    QString maxId = getMaxPictureId();
    QString newId = QString::number(maxId.toUInt() + 1);
    return newId;
}


QString DataDB::getIpAddress(QString userId)
{
    QSqlQuery query;
    query.prepare("SELECT ipAddress FROM UserIp WHERE userId = ?");
    query.addBindValue(userId);

    if (!query.exec()) {
        qDebug() << "获取IP地址失败: " << query.lastError().text();
        return QString("Failed");
    }

    if (query.next()) {
        QString ipAddress = query.value("ipAddress").toString();
        return ipAddress;
    }

    return QString("Half Failed");
}

QString DataDB::getMaxGroupId()
{
    QString maxGroupId;

    QSqlQuery query;
    query.prepare("SELECT MAX(groupId) FROM GroupInfo");

    if (query.exec() && query.next()) {
        maxGroupId = query.value(0).toString();
    } else {
        qWarning() << "获取最大群组id失败:" << query.lastError().text();
    }

    return maxGroupId;
}

QString DataDB::getMaxPictureId()
{
    return "";
}

void DataDB::offLine(QString userIp)
{
    QSqlQuery query;
    query.prepare("DELETE FROM UserIp WHERE ipAddress = ?");
    query.addBindValue(userIp);

    if (!query.exec()) {
        qDebug() << "下线失败: " << query.lastError().text();
    } else {
        qDebug() << "下线成功";
    }
}

void DataDB::login(QString userId, QString userIp)
{
    QSqlQuery query;
    query.prepare("INSERT INTO UserIp (userId, ipAddress) VALUES (:id, :ip)");
    query.bindValue(":id",userId);
    query.bindValue(":ip",userIp);
    qDebug() << "数据库文件创建成功";

    if (!query.exec()) {
        qDebug() << "上线失败: " << query.lastError().text();
    } else {
        qDebug() << "上线成功";
    }
}

bool DataDB::checkIdExist(QString userId)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM UserInfo WHERE userId = :id");
    query.bindValue(":id", userId);
    qDebug()<<userId<<"USERID ID ID ID ID ";

    if(!query.exec())
    {
        qWarning()<<"执行失败:"<< query.lastError().text();
    }
    else
    {
        if(!query.next())
        {
            qDebug()<<"账号未存在";
            return false;
        }
        else
        {
            qDebug()<<"账号已存在";
            return true;
        }
    }

//    if (query.exec() && query.next()) {
//        int count = query.value(0).toInt();
//        if (count > 0){
//            qDebug() << "用户名已存在！";
//            return true;
//        }
//    } else {
//        qWarning() << "检查用户id是否重复失败:" << query.lastError().text();
//    }

    return true;
}

bool DataDB::checkOnLine(QString userId)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM UserIp WHERE userId = :id");
    query.bindValue(":id", userId);

    if(!query.exec())
    {
        qWarning()<<"执行失败:"<< query.lastError().text();
    }
    else
    {
        if(!query.next())
        {
            qDebug()<<"账号不在线";
            return false;
        }
        else
        {
            qDebug()<<"账号正在线";
            return true;
        }
    }
}

bool DataDB::isFriend(QString userId1, QString userId2)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM Friend WHERE userId1 = :id1 AND userId2 = :id2");
    query.bindValue(":id1", userId1);
    query.bindValue(":id2", userId2);
    qDebug()<<"USERID ID ID ID ID ";

    if(!query.exec())
    {
        qWarning()<<"执行失败:"<< query.lastError().text();
    }
    else
    {
        if(!query.next())
        {
            qDebug()<<"朋友未存在";
            return false;
        }
        else
        {
            qDebug()<<"朋友已存在";
            return true;
        }
    }
}

void DataDB::editUserAvatar(QString userId, QString picture)
{
    QSqlQuery query;
    query.prepare("UPDATE UserInfo SET picture = ? WHERE userId = ?");
    query.addBindValue(picture);
    query.addBindValue(userId);

    if (!query.exec()) {
        qWarning() << "修改用户头像失败:" << query.lastError().text();
    }else{
        qDebug() << "修改用户头像成功:";
    }
}

void DataDB::editUserName(QString userId, QString name)
{
    QSqlQuery query;
    query.prepare("UPDATE UserInfo SET name = ? WHERE userId = ?");
    query.addBindValue(name);
    query.addBindValue(userId);

    if (!query.exec()) {
        qWarning() << "修改用户名失败:" << query.lastError().text();
    }else{
        qDebug() << "修改用户名成功:";
    }
}

bool DataDB::checkInGroup(QString userId, QString groupId)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM GroupMembers WHERE userId = ? AND groupId = ?");
    query.addBindValue(userId);
    query.addBindValue(groupId);
    if(query.exec())
    {
        qDebug() << "成功执行" ;
        if(query.next())
            return true;
        else
            return false;
    }
    qDebug()<<"执行失败";
    return false;
}




























