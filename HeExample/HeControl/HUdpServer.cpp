#include "HUdpServer_p.h"
#include <QtNetwork/QUdpSocket>
#include <QtNetwork/QNetworkDatagram>

HE_CONTROL_BEGIN_NAMESPACE

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

bool HUdpServer::isRunning()
{
    return d_ptr->isRunning;
}

bool HUdpServer::start()
{
    if (isRunning())
        return true;
    auto addr = d_ptr->listenIP.isEmpty() ? QHostAddress::AnyIPv4 : QHostAddress(d_ptr->listenIP);
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

void HUdpServer::setListenIP(const QString &value)
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
    for (auto c : d_ptr->clients)
    {
        auto list = c.split(":");
        sendData(list.at(0), list.at(1).toUShort(), data);
    }
}

void HUdpServer::sendData(const QString &ip, int port, const QByteArray &data)
{
    if (d_ptr->socket->writeDatagram(data, QHostAddress(ip), port) == -1)
        clientDisconnected(ip, port);
    else
        emit sentData(ip, port, data);
}

void HUdpServer::incomingConnection(const QString &ip, int port)
{
    auto text = QString("%1:%2").arg(ip).arg(port);
    if (d_ptr->clients.contains(text))
        return;
    d_ptr->clients.insert(text);
    emit clientConnected(ip, port);
}

void HUdpServer::disconnectClient()
{
    auto cs = d_ptr->clients;
    for (auto c : cs)
    {
        auto list = c.split(":");
        disconnectClient(list.at(0), list.at(1).toUShort());
    }
}

void HUdpServer::disconnectClient(const QString &ip, int port)
{
    auto key = QString("%1:%2").arg(ip).arg(port);
    if (!d_ptr->clients.contains(key))
        return;
    emit clientDisconnected(ip, port);
    d_ptr->clients.remove(key);
}

void HUdpServer::handleReadyRead()
{
    while (d_ptr->socket->hasPendingDatagrams())
    {
        auto datagram = d_ptr->socket->receiveDatagram();
        auto ip = datagram.senderAddress().toString().replace("::ffff:", "");
        auto port = datagram.senderPort();
        auto data = datagram.data();
        if (ip.isEmpty() || data.isEmpty())
            continue;
        incomingConnection(ip, port);
        emit receiveData(ip, port, data);
    }
}

void HUdpServer::init()
{
    d_ptr->socket = new QUdpSocket(this);
    connect(d_ptr->socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(stop()));
    connect(d_ptr->socket, &QUdpSocket::disconnected, this, &HUdpServer::stop);
    connect(d_ptr->socket, &QUdpSocket::readyRead, this, &HUdpServer::handleReadyRead);
}

HE_CONTROL_END_NAMESPACE
