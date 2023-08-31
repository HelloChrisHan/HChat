#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include"clientvm.h"
#include"avatarimageprovider.h"
#include"testnetwork.h"
//#include<QThread>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    QCoreApplication::setOrganizationName("Some organization");

    qmlRegisterType<Message>("Message",1,0,"Message");
    qmlRegisterType<Chat>("Chat",1,0,"Chat");
//    auto vm = new ClientVM();
    auto avatarProvider=new AvatarImageProvider();
    auto network=new TestNetwork();
    engine.addImageProvider("AvatarImgProvider",avatarProvider);
    engine.rootContext()->setContextProperty("vm",new ClientVM(avatarProvider,network));
    engine.load(url);

    return app.exec();
}
