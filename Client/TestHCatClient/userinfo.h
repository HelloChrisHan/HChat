#ifndef USERINFO_H
#define USERINFO_H
#include<QObject>

class UserInfo
{
public:
    UserInfo(QString userId="", QString name="", QString avatar="");

    QString userId();
    QString name();
    QString avatar();
    void setUserId(QString);
    void setName(QString);
    void setAvatar(QString);
private:
    QString m_userId;
    QString m_name;
    QString m_avatar;
};

#endif // USERINFO_H
