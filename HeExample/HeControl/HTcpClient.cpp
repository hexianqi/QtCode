#include "HTcpClient_p.h"
#include <QtNetwork/QHostAddress>

HE_CONTROL_BEGIN_NAMESPACE

HTcpClient::HTcpClient(QObject *parent) :
    QTcpSocket(parent),
    d_ptr(new HTcpClientPrivate)
{
    init();
}

HTcpClient::HTcpClient(HTcpClientPrivate &p, QObject *parent) :
    QTcpSocket(parent),
    d_ptr(&p)
{
    init();
}

HTcpClient::~HTcpClient()
{
}

QString HTcpClient::ip() const
{
    return peerAddress().toString();
}

int HTcpClient::port() const
{
    return peerPort();
}

void HTcpClient::sendData(const QByteArray &value)
{
    write(value);
    emit sentData(ip(), port(), value);
}

void HTcpClient::handleReadyRead()
{
    auto data = readAll();
    if (data.length() <= 0)
        return;
    emit receiveData(ip(), port(), data);
}

void HTcpClient::init()
{
    connect(this, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(deleteLater()));
    connect(this, &HTcpClient::disconnected, this, &HTcpClient::deleteLater);
    connect(this, &HTcpClient::readyRead, this, &HTcpClient::handleReadyRead);
}

HE_CONTROL_END_NAMESPACE
