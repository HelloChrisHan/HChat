#ifndef CLIENTSOCKET_H
#define CLIENTSOCKET_H
#include <QTcpSocket>
#include <QDebug>
#include <QTcpServer>

class ClientSocket:public QObject
{
    Q_OBJECT
public:
    ClientSocket();
private:
    QTcpSocket *socket;
public:
    void connectToServer();
    void sendMessage(QString);
    void receiveMessage();
signals:
    void receivedMessage(QString);
};

#endif // CLIENTSOCKET_H
