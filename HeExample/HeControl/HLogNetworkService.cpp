#include "HLogNetworkService_p.h"
#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QTcpServer>

HE_BEGIN_NAMESPACE

HLogNetworkService::HLogNetworkService() :
    HAbstractService(*new HLogNetworkServicePrivate)
{
    init();
}

HLogNetworkService::~HLogNetworkService()
{
    stop();
}

bool HLogNetworkService::start()
{
    Q_D(HLogNetworkService);
    if (!HAbstractService::start())
        return false;
    d->server->listen(QHostAddress::AnyIPv4, d->listenPort);
    return true;
}

bool HLogNetworkService::stop()
{
    Q_D(HLogNetworkService);
    if (!HAbstractService::stop())
        return false;
    if (d->socket != nullptr)
        d->socket->disconnectFromHost();
    d->server->close();
    return true;
}

void HLogNetworkService::setListenPort(int value)
{
    Q_D(HLogNetworkService);
    d->listenPort = value;
}

void HLogNetworkService::sendData(const QString &value)
{
    Q_D(HLogNetworkService);
    if (d->socket == nullptr || !d->socket->isOpen())
        return;
    d->socket->write(value.toUtf8());
    d->socket->flush();
}

void HLogNetworkService::init()
{
    Q_D(HLogNetworkService);
    d->server = new QTcpServer(this);
    connect(d->server, &QTcpServer::newConnection, this, &HLogNetworkService::handleNewConnection);
}

void HLogNetworkService::handleNewConnection()
{
    Q_D(HLogNetworkService);
    while (d->server->hasPendingConnections())          // 限定就一个连接
        d->socket = d->server->nextPendingConnection();
}

HE_END_NAMESPACE
