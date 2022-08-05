#include "HWebClient_p.h"
#include "HNetworkHelper.h"
#include <QtWebSockets/QWebSocket>

HE_BEGIN_NAMESPACE

HWebClient::HWebClient(QWebSocket *socket, QObject *parent) :
    QObject(parent),
    d_ptr(new HWebClientPrivate)
{
    d_ptr->socket = socket;
    connect(d_ptr->socket, SIGNAL(disconnected()), this, SLOT(handleDisconnected()));
    connect(d_ptr->socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(handleError()));
    connect(d_ptr->socket, SIGNAL(binaryMessageReceived(const QByteArray &)), this, SLOT(handleBinaryMessageReceived(const QByteArray &)));
    connect(d_ptr->socket, SIGNAL(textMessageReceived(const QString &)), this, SLOT(handleTextMessageReceived(const QString &)));
}

HWebClient::~HWebClient() = default;

QString HWebClient::address()
{
    return HNetworkHelper::toString(d_ptr->socket->peerAddress());
}

int HWebClient::port()
{
    return d_ptr->socket->peerPort();
}

void HWebClient::sendData(const QString &value)
{
    if (d_ptr->socket->sendTextMessage(value) != -1)
        emit sentData(address(), port(), value);
}

void HWebClient::sendData(const QByteArray &value)
{
    if (d_ptr->socket->sendBinaryMessage(value) != -1)
        emit sentData(address(), port(), value);
}

void HWebClient::abort()
{
    d_ptr->socket->abort();
}

void HWebClient::handleError()
{
    emit error(address(), port(), d_ptr->socket->errorString());
}

void HWebClient::handleDisconnected()
{
    emit disconnected(address(), port());
    d_ptr->socket->deleteLater();
    this->deleteLater();
}

void HWebClient::handleTextMessageReceived(const QString &data)
{
    emit receiveData(address(), port(), data);
}

void HWebClient::handleBinaryMessageReceived(const QByteArray &data)
{
    emit receiveData(address(), port(), data);
}

HE_END_NAMESPACE
