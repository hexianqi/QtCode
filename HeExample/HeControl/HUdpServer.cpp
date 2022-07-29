#include "HUdpServer_p.h"
#include "HNetworkHelper.h"
#include <QtNetwork/QUdpSocket>
#include <QtNetwork/QNetworkDatagram>

HE_BEGIN_NAMESPACE

HUdpServer::HUdpServer(QObject *parent) :
    QObject(parent),
    d_ptr(new HUdpServerPrivate)
{
    init();
}

HUdpServer::HUdpServer(HUdpServerPrivate &p, QObject *parent) :
    QObject(parent),
    d_ptr(&p)
{
    init();
}

HUdpServer::~HUdpServer()
{
    stop();
}

QString HUdpServer::errorString()
{
    return d_ptr->socket->errorString();
}

bool HUdpServer::isRunning()
{
    return d_ptr->isRunning;
}

bool HUdpServer::start()
{
    if (isRunning())
        return true;
    auto addr = d_ptr->listenAddress.isEmpty() ? QHostAddress::AnyIPv4 : QHostAddress(d_ptr->listenAddress);
    d_ptr->isRunning = d_ptr->socket->bind(addr, d_ptr->listenPort);
    return d_ptr->isRunning;
}

void HUdpServer::stop()
{
    if (!isRunning())
        return;
    disconnectClient();
    d_ptr->isRunning = false;
    d_ptr->socket->abort();
}

void HUdpServer::setListenAddress(const QString &value)
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

void HUdpServer::setListenPort(int value)
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

void HUdpServer::sendData(const QByteArray &data)
{
    for (auto client : d_ptr->clients)
    {
        auto list = client.split(":");
        sendData(list.at(0), list.at(1).toUShort(), data);
    }
}

void HUdpServer::sendData(const QString &address, int port, const QByteArray &data)
{
    if (d_ptr->socket->writeDatagram(data, QHostAddress(address), port) == -1)
        disconnected(address, port);
    else
        emit sentData(address, port, data);
}

void HUdpServer::incomingConnection(const QString &address, int port)
{
    auto text = QString("%1:%2").arg(address).arg(port);
    if (d_ptr->clients.contains(text))
        return;
    d_ptr->clients.insert(text);
    emit connected(address, port);
}

void HUdpServer::disconnectClient()
{
    auto cs = d_ptr->clients;
    for (const auto &client : cs)
    {
        auto list = client.split(":");
        disconnectClient(list.at(0), list.at(1).toUShort());
    }
}

void HUdpServer::disconnectClient(const QString &address, int port)
{
    auto key = QString("%1:%2").arg(address).arg(port);
    if (!d_ptr->clients.contains(key))
        return;
    emit disconnected(address, port);
    d_ptr->clients.remove(key);
}

void HUdpServer::handleReadyRead()
{
    while (d_ptr->socket->hasPendingDatagrams())
    {
        auto datagram = d_ptr->socket->receiveDatagram();
        auto address = HNetworkHelper::toString(datagram.senderAddress());
        auto port = datagram.senderPort();
        auto data = datagram.data();
        if (address.isEmpty() || data.isEmpty())
            continue;
        incomingConnection(address, port);
        emit receiveData(address, port, data);
    }
}

void HUdpServer::handleError()
{
    emit error(HNetworkHelper::toString(d_ptr->socket->peerAddress()), d_ptr->socket->peerPort(), d_ptr->socket->errorString());
}

void HUdpServer::init()
{
    d_ptr->socket = new QUdpSocket(this);
    connect(d_ptr->socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(handleError()));
    connect(d_ptr->socket, &QUdpSocket::readyRead, this, &HUdpServer::handleReadyRead);
    connect(d_ptr->socket, &QUdpSocket::disconnected, this, &HUdpServer::stop);
}

HE_END_NAMESPACE
