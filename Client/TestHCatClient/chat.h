#ifndef FRIEND_H
#define FRIEND_H
#include<QObject>

class Chat: public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name NOTIFY nameChanged)
    Q_PROPERTY(QString id READ id CONSTANT)
    Q_PROPERTY(QString avatar READ avatar CONSTANT)
public:
    Chat(QString name="", QString id="", QString avatar="");
    QString name();
    QString id();
    QString avatar();
signals:
    void nameChanged();
private:
//    QImage avatar;
    QString m_name;
    QString m_id;
    QString m_avatar;
};

#endif // FRIEND_H
