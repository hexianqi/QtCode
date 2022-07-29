#include "HTcpClient_p.h"
#include "HNetworkHelper.h"
#include <QtNetwork/QHostAddress>
#include <QtNetwork/QTcpSocket>

HE_BEGIN_NAMESPACE

HTcpClient::HTcpClient(QTcpSocket *socket, QObject *parent) :
    QObject(parent),
    d_ptr(new HTcpClientPrivate)
{
    d_ptr->socket = socket;
    connect(d_ptr->socket, SIGNAL(disconnected()), this, SLOT(handleDisconnected()));
    connect(d_ptr->socket, SIGNAL(readyRead()), this, SLOT(handleReadyRead()));
    connect(d_ptr->socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(handleError()));
}

HTcpClient::~HTcpClient() = default;

QString HTcpClient::address()
{
    return HNetworkHelper::toString(d_ptr->socket->peerAddress());
}

int HTcpClient::port()
{
    return d_ptr->socket->peerPort();
}

void HTcpClient::sendData(const QByteArray &value)
{
    if (d_ptr->socket->write(value) != -1)
        emit sentData(address(), port(), value);
}

void HTcpClient::disconnectFromHost()
{
    d_ptr->socket->disconnectFromHost();
}

void HTcpClient::abort()
{
    d_ptr->socket->abort();
}

void HTcpClient::handleReadyRead()
{
    auto data = d_ptr->socket->readAll();
    if (data.length() <= 0)
        return;
    emit receiveData(address(), port(), data);
}

void HTcpClient::handleError()
{
    emit error(address(), port(), d_ptr->socket->errorString());
}

void HTcpClient::handleDisconnected()
{
    emit disconnected(address(), port());
    d_ptr->socket->deleteLater();
    this->deleteLater();
}

HE_END_NAMESPACE
