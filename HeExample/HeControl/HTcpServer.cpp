#include "HTcpServer_p.h"
#include "HTcpClient.h"
#include <QDebug>

HE_CONTROL_BEGIN_NAMESPACE

HTcpServer::HTcpServer(QObject *parent) :
    QTcpServer(parent),
    d_ptr(new HTcpServerPrivate)
{
}

HTcpServer::HTcpServer(HTcpServerPrivate &p, QObject *parent) :
    QTcpServer(parent),
    d_ptr(&p)
{
}

HTcpServer::~HTcpServer()
{
    stop();
}

bool HTcpServer::isRunning()
{
    return isListening();
}

bool HTcpServer::start()
{
    if (isRunning())
        return true;
    auto addr = d_ptr->listenIP.isEmpty() ? QHostAddress::AnyIPv4 : QHostAddress(d_ptr->listenIP);
    return listen(addr, d_ptr->listenPort);
}

void HTcpServer::stop()
{
    if (!isRunning())
        return;
    disconnectClient();
    close();
}

void HTcpServer::setListenIP(const QString &value)
{
    if (d_ptr->listenIP == value)
        return;
    d_ptr->listenIP = value;
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
    for (auto c : d_ptr->clients)
        c->sendData(data);
}

void HTcpServer::sendData(const QString &ip, int port, const QByteArray &data)
{
    auto key = QString("%1:%2").arg(ip).arg(port);
    if (!d_ptr->clients.contains(key))
        return;
    d_ptr->clients.value(key)->sendData(data);
}

void HTcpServer::disconnectClient()
{
    for (auto c : d_ptr->clients)
        c->disconnectFromHost();
}

void HTcpServer::disconnectClient(const QString &ip, int port)
{
    auto key = QString("%1:%2").arg(ip).arg(port);
    if (!d_ptr->clients.contains(key))
        return;
    d_ptr->clients.value(key)->disconnectFromHost();
}

void HTcpServer::incomingConnection(int handle)
{
    if (d_ptr->clients.size() > maxPendingConnections())
        return;
    auto client = new HTcpClient(this);
    client->setSocketDescriptor(handle);
    connect(client, &HTcpClient::disconnected, this, &HTcpServer::handleClientDisconnected);
    connect(client, &HTcpClient::sentData, this, &HTcpServer::sentData);
    connect(client, &HTcpClient::receiveData, this, &HTcpServer::receiveData);
    d_ptr->clients.insert(QString("%1:%2").arg(client->ip()).arg(client->port()), client);
    emit clientConnected(client->ip(), client->port());
}

void HTcpServer::handleClientDisconnected()
{
    auto client = qobject_cast<HTcpClient *>(sender());
    if (client == nullptr)
        return;
    auto key = QString("%1:%2").arg(client->ip()).arg(client->port());
    if (!d_ptr->clients.contains(key))
        return;
    emit clientDisconnected(client->ip(), client->port());
    d_ptr->clients.remove(key);
}

HE_CONTROL_END_NAMESPACE
