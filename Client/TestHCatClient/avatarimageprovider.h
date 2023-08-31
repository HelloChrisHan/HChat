#ifndef AVATARIMAGEPROVIDER_H
#define AVATARIMAGEPROVIDER_H
#include<QQuickImageProvider>

class AvatarImageProvider: public QQuickImageProvider
{
public:
    AvatarImageProvider();


    QImage requestImage(const QString &id, QSize *size, const QSize &requestedSize) override;
    void addImage(QString id, QImage image);

private:
    QHash<QString,QImage> m_imgMap;

};

#endif // AVATARIMAGEPROVIDER_H
