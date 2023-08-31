#include "clientsocket.h"

ClientSocket::ClientSocket()
{
    connectToServer();
}

void ClientSocket::connectToServer()
{
    socket = new QTcpSocket(this);
    socket->connectToHost("127.0.0.1",9999);
    connect(
        socket,
        &QTcpSocket::readyRead,
        this,
        &ClientSocket::receiveMessage
    );
}

void ClientSocket::sendMessage(QString msg)
{
    qDebug()<<"send"<<msg;
    socket->waitForBytesWritten();
    socket->write(msg.toUtf8());
}

void ClientSocket::receiveMessage()
{
    emit receivedMessage(QString(socket->readAll().data()));
}
