#include "mytcpclient.h"

MyTcpClient::MyTcpClient(QObject *parent) : QTcpSocket(parent)
{
    mySocket = new QTcpSocket();
}

void MyTcpClient::setName(QString name)
{
    m_name = name;
}

QString MyTcpClient::getName()
{
    return m_name;
}

void MyTcpClient::setPass(QString pass)
{
    m_password = pass;
}

QString MyTcpClient::getPass()
{
    return m_password;
}
