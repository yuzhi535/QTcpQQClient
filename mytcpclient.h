#ifndef MYTCPCLENT_H
#define MYTCPCLENT_H

#include <QObject>
#include <QTcpSocket>
#include <QHostAddress>

class MyTcpClient : public QTcpSocket
{
    Q_OBJECT
public:
    explicit MyTcpClient(QObject *parent = nullptr);

signals:

private:
    QTcpSocket* mySocket;
};

#endif // MYTCPCLENT_H
