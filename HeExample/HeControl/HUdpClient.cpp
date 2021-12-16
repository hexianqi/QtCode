#include "HUdpClient_p.h"
#include <QtNetwork/QNetworkDatagram>

HE_BEGIN_NAMESPACE

HUdpClient::HUdpClient(QObject *parent) :
    QUdpSocket(parent),
    d_ptr(new HUdpClientPrivate)
{
    init();
}

HUdpClient::HUdpClient(HUdpClientPrivate &p, QObject *parent) :
    QUdpSocket(parent),
    d_ptr(&p)
{
    init();
}

HUdpClient::~HUdpClient() = default;

void HUdpClient::sendData(const QString &address, int port, const QByteArray &value)
{
    if (writeDatagram(value, QHostAddress(address), port) != -1)
        emit sentData(address, port, value);
}

void HUdpClient::handleReadyRead()
{
    while (hasPendingDatagrams())
    {
        auto datagram = receiveDatagram();
        auto ip = datagram.senderAddress().toString().replace("::ffff:", "");
        auto port = datagram.senderPort();
        auto data = datagram.data();
        if (ip.isEmpty() || data.isEmpty())
            continue;
        emit receiveData(ip, port, data);
    }
}

void HUdpClient::init()
{
    connect(this, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(deleteLater()));
    connect(this, &HUdpClient::disconnected, this, &HUdpClient::deleteLater);
    connect(this, &HUdpClient::readyRead, this, &HUdpClient::handleReadyRead);
}

HE_END_NAMESPACE
