#ifndef GROUPINFO_H
#define GROUPINFO_H

#include <QObject>

class GroupInfo: public QObject
{
    Q_OBJECT
public:
    GroupInfo();
    GroupInfo(QString _groupId, QString _ownerId, QString _name, QByteArray _picture);
    GroupInfo(const GroupInfo& _groupInfo);
    QString groupId;
    QString ownerId;
    QString name;
    QByteArray picture;
};

#endif // GROUPINFO_H
