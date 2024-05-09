// chatserver.cpp

#include "chatserver.h"

ChatServer::ChatServer(QObject* parent) : QTcpServer(parent)
{
    listen(QHostAddress::Any, 1234); // Listen on all available interfaces on port 1234
}

void ChatServer::incomingConnection(qintptr socketDescriptor)
{
    QTcpSocket* clientSocket = new QTcpSocket(this);
    clientSocket->setSocketDescriptor(socketDescriptor);

    connect(clientSocket, &QTcpSocket::readyRead, this, &ChatServer::readyRead);
    connect(clientSocket, &QTcpSocket::disconnected, this, &ChatServer::disconnected);

    clients.append(clientSocket);
}

void ChatServer::readyRead()
{
    QTcpSocket* senderSocket = qobject_cast<QTcpSocket*>(sender());
    if (!senderSocket)
        return;

    QByteArray message = senderSocket->readAll();
    // Broadcast the message to all clients except the sender
    for (QTcpSocket* client : qAsConst(clients)) {
        if (client != senderSocket) {
            client->write(message);
        }
    }
}

void ChatServer::disconnected()
{
    QTcpSocket* clientSocket = qobject_cast<QTcpSocket*>(sender());
    if (!clientSocket)
        return;

    clients.removeOne(clientSocket);
    clientSocket->deleteLater();
}
