#ifndef GROUPINFO_H
#define GROUPINFO_H
#include<QObject>

class GroupInfo
{
public:
    GroupInfo(QString groupId="", QString name="", QString avatar="", QList<QString> members=QList<QString>());

    QString groupId();
    QString name();
    QString avatar();
    QList<QString> members();
    void setGroupId(QString);
    void setName(QString);
    void setAvatar(QString);
private:
    QString m_groupId;
    QString m_name;
    QString m_avatar;
    QList<QString> m_members;
};

#endif // GROUPINFO_H
