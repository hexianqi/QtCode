#include "HTcpServer_p.h"
#include "HTcpClient.h"

HE_BEGIN_NAMESPACE

HTcpServer::HTcpServer(QObject *parent) :
    QTcpServer(parent),
    d_ptr(new HTcpServerPrivate)
{
    connect(this, &HTcpServer::newConnection, this, &HTcpServer::handleNewConnection);
}

HTcpServer::HTcpServer(HTcpServerPrivate &p, QObject *parent) :
    QTcpServer(parent),
    d_ptr(&p)
{
    connect(this, &HTcpServer::newConnection, this, &HTcpServer::handleNewConnection);
}

HTcpServer::~HTcpServer() = default;

bool HTcpServer::isRunning()
{
    return isListening();
}

bool HTcpServer::start()
{
    if (isRunning())
        return true;
    auto addr = d_ptr->listenAddress.isEmpty() ? QHostAddress::AnyIPv4 : QHostAddress(d_ptr->listenAddress);
    return listen(addr, d_ptr->listenPort);
}

void HTcpServer::stop()
{
    if (!isRunning())
        return;
    disconnectClient();
    close();
}

void HTcpServer::setListenAddress(const QString &value)
{
    if (d_ptr->listenAddress == value)
        return;
    d_ptr->listenAddress = value;
    if (isRunning())
    {
        stop();
        start();
    }
}

void HTcpServer::setListenPort(int value)
{
    if (d_ptr->listenPort == value)
        return;
    d_ptr->listenPort = value;
    if (isRunning())
    {
        stop();
        start();
    }
}

void HTcpServer::sendData(const QByteArray &data)
{
    for (auto client : d_ptr->clients.values())
        client->sendData(data);
}

void HTcpServer::sendData(const QString &address, int port, const QByteArray &data)
{
    auto key = QString("%1:%2").arg(address).arg(port);
    if (!d_ptr->clients.contains(key))
        return;
    d_ptr->clients.value(key)->sendData(data);
}

void HTcpServer::disconnectClient()
{
    for (auto c : d_ptr->clients.values())
        c->abort();
}

void HTcpServer::disconnectClient(const QString &address, int port)
{
    auto key = QString("%1:%2").arg(address).arg(port);
    if (!d_ptr->clients.contains(key))
        return;
    d_ptr->clients.value(key)->abort();
}

void HTcpServer::handleNewConnection()
{
    auto client = new HTcpClient(nextPendingConnection(), this);
    connect(client, &HTcpClient::disconnected, this, &HTcpServer::handleDisconnected);
    connect(client, &HTcpClient::error, this, &HTcpServer::error);
    connect(client, &HTcpClient::sentData, this, &HTcpServer::sentData);
    connect(client, &HTcpClient::receiveData, this, &HTcpServer::receiveData);
    d_ptr->clients.insert(QString("%1:%2").arg(client->address()).arg(client->port()), client);
    emit connected(client->address(), client->port());
}

void HTcpServer::handleDisconnected()
{
    auto client = qobject_cast<HTcpClient *>(sender());
    if (client == nullptr)
        return;
    auto key = QString("%1:%2").arg(client->address()).arg(client->port());
    if (!d_ptr->clients.contains(key))
        return;
    emit disconnected(client->address(), client->port());
    d_ptr->clients.remove(key);
}

HE_END_NAMESPACE
