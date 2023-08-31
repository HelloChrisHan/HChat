#ifndef MESSAGE_H
#define MESSAGE_H
#include<QObject>
#include<QImage>

class Message:public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString msg READ msg WRITE setMsg NOTIFY msgChanged) // text msg
    Q_PROPERTY(QString emote READ emote CONSTANT)                   // emote msg
    Q_PROPERTY(QString pic READ pic CONSTANT)                        // pic msg
    Q_PROPERTY(QString avatar READ avatar CONSTANT)                 // user avatar
    Q_PROPERTY(bool self READ isSelf CONSTANT)                      // isSelf
    Q_PROPERTY(QString type READ type CONSTANT)                     // msg type
    Q_PROPERTY(QString name READ name CONSTANT)
public:
    Message(
            bool isSelf=false,
            QString avatar="",
            QString name="",
            QString type="",
            QString msg="",
            QString emote="",
            QString pic="",
            QObject* parent=nullptr
            );
    QString msg();
    QString emote();
    QString pic();//TODO
    QString avatar();
    bool isSelf();
    void setMsg(QString);
    QString type();
    QString name();
signals:
    void msgChanged();
private:
    bool m_isSelf;
    QString m_avatar;
    QString m_name;
    QString m_type;
    QString m_msg;
    QString m_emote;
    QString m_pic;
};

#endif // MESSAGE_H
