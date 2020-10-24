#include "mytcpclient.h"

MyTcpClient::MyTcpClient(QObject *parent) : QTcpSocket(parent)
{
    mySocket = new QTcpSocket();
}
