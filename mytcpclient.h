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
    void setName(QString name);
    QString getName();
    void setPass(QString pass);
    QString getPass();

signals:

private:
    QTcpSocket* mySocket;
    QString m_name;
    QString m_password;
};

#endif // MYTCPCLENT_H
