// chatserver.h

#ifndef CHATSERVER_H
#define CHATSERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QList>

class ChatServer : public QTcpServer
{
    Q_OBJECT
public:
    ChatServer(QObject* parent = nullptr);

protected:
    void incomingConnection(qintptr socketDescriptor) override;

private slots:
    void readyRead();
    void disconnected();

private:
    QList<QTcpSocket*> clients;
};

#endif // CHATSERVER_H
