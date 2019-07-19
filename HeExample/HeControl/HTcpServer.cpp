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

bool HTcpServer::start()
{
    return listen(QHostAddress::AnyIPv4, d_ptr->listenPort);
}

void HTcpServer::stop()
{
    for (auto c : d_ptr->clients.values())
        c->disconnectFromHost();
    close();
}

void HTcpServer::setListenPort(quint16 value)
{
    if (d_ptr->listenPort == value)
        return;
    d_ptr->listenPort = value;
    if (isListening())
    {
        stop();
        start();
    }
}

void HTcpServer::sendData(QString ip, int port, QByteArray data)
{
    auto key = QString("%1:%2").arg(ip).arg(port);
    if (!d_ptr->clients.contains(key))
        return;
    d_ptr->clients.value(key)->sendData(data);
}

void HTcpServer::sendData(QByteArray data)
{
    for (auto c : d_ptr->clients)
        c->sendData(data);
}

void HTcpServer::disconnectClient(QString ip, int port)
{
    auto key = QString("%1:%2").arg(ip).arg(port);
    if (!d_ptr->clients.contains(key))
        return;
    d_ptr->clients.value(key)->disconnectFromHost();
}

void HTcpServer::incomingConnection(int handle)
{
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
