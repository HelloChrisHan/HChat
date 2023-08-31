#include "avatarimageprovider.h"

AvatarImageProvider::AvatarImageProvider()
    :QQuickImageProvider(QQuickImageProvider::Image)
{

}

QImage AvatarImageProvider::requestImage(const QString &id, QSize *size, const QSize &requestedSize)
{
    return m_imgMap[id];
}

void AvatarImageProvider::addImage(QString id, QImage image)
{
    m_imgMap[id]=image;
}
