#include "HWebServer_p.h"
#include "HWebClient.h"

HE_BEGIN_NAMESPACE

HWebServer::HWebServer(const QString &serverName, QWebSocketServer::SslMode secureMode, QObject *parent) :
    QWebSocketServer(serverName, secureMode, parent),
    d_ptr(new HWebServerPrivate)
{
    connect(this, &HWebServer::newConnection, this, &HWebServer::handleNewConnection);
}

HWebServer::~HWebServer() = default;

bool HWebServer::isRunning()
{
    return isListening();
}

bool HWebServer::start()
{
    if (isRunning())
        return true;
    auto addr = d_ptr->listenAddress.isEmpty() ? QHostAddress::AnyIPv4 : QHostAddress(d_ptr->listenAddress);
    return listen(addr, d_ptr->listenPort);
}

void HWebServer::stop()
{
    if (!isRunning())
        return;
    disconnectClient();
    close();
}

void HWebServer::setListenAddress(const QString &value)
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

void HWebServer::setListenPort(int value)
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

void HWebServer::sendData(const QString &data)
{
    for (auto client : d_ptr->clients.values())
        client->sendData(data);
}

void HWebServer::sendData(const QByteArray &data)
{
    for (auto client : d_ptr->clients.values())
        client->sendData(data);
}

void HWebServer::sendData(const QString &address, int port, const QString &data)
{
    auto key = QString("%1:%2").arg(address).arg(port);
    if (!d_ptr->clients.contains(key))
        return;
    d_ptr->clients.value(key)->sendData(data);
}

void HWebServer::sendData(const QString &address, int port, const QByteArray &data)
{
    auto key = QString("%1:%2").arg(address).arg(port);
    if (!d_ptr->clients.contains(key))
        return;
    d_ptr->clients.value(key)->sendData(data);
}

void HWebServer::disconnectClient()
{
    for (auto c : d_ptr->clients.values())
        c->abort();
}

void HWebServer::disconnectClient(const QString &address, int port)
{
    auto key = QString("%1:%2").arg(address).arg(port);
    if (!d_ptr->clients.contains(key))
        return;
    d_ptr->clients.value(key)->abort();
}

void HWebServer::handleNewConnection()
{
    auto client = new HWebClient(nextPendingConnection(), this);
    connect(client, SIGNAL(disconnected(QString, int)), this, SLOT(handleDisconnected()));
    connect(client, SIGNAL(error(QString, int, QString)), this, SIGNAL(error(QString, int, QString)));
    connect(client, SIGNAL(sentData(QString, int, QString)), this, SIGNAL(sentData(QString, int, QString)));
    connect(client, SIGNAL(sentData(QString, int, QByteArray)), this, SIGNAL(sentData(QString, int, QByteArray)));
    connect(client, SIGNAL(receiveData(QString, int, QString)), this, SIGNAL(receiveData(QString, int, QString)));
    connect(client, SIGNAL(receiveData(QString, int, QByteArray)), this, SIGNAL(receiveData(QString, int, QByteArray)));
    d_ptr->clients.insert(QString("%1:%2").arg(client->address()).arg(client->port()), client);
    emit connected(client->address(), client->port());
}

void HWebServer::handleDisconnected()
{
    auto client = qobject_cast<HWebClient *>(sender());
    if (client == nullptr)
        return;
    auto key = QString("%1:%2").arg(client->address()).arg(client->port());
    if (!d_ptr->clients.contains(key))
        return;
    emit disconnected(client->address(), client->port());
    d_ptr->clients.remove(key);
}


HE_END_NAMESPACE
