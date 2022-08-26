#include "HNtpClient_p.h"
#include <QtCore/QDateTime>
#include <QtNetwork/QUdpSocket>
#include <QtNetwork/QNetworkDatagram>

HE_BEGIN_NAMESPACE

HNtpClient::HNtpClient(QObject *parent) :
    QObject(parent),
    d_ptr(new HNtpClientPrivate)
{
    init();
}

HNtpClient::HNtpClient(HNtpClientPrivate &p, QObject *parent) :
    QObject(parent),
    d_ptr(&p)
{
    init();
}

HNtpClient::~HNtpClient()
{
    d_ptr->socket->abort();
}

QString HNtpClient::host() const
{
    return d_ptr->host;
}

void HNtpClient::setHost(const QString &value)
{
    if (d_ptr->host == value)
        return;
    d_ptr->host = value;
}

void HNtpClient::getDateTime()
{
    d_ptr->socket->abort();
    d_ptr->socket->connectToHost(d_ptr->host, 123);
}

void HNtpClient::sendData()
{
    qint8 LI = 0;
    qint8 VN = 3;
    qint8 MODE = 3;
    qint8 STRATUM = 0;
    qint8 POLL = 4;
    qint8 PREC = -6;
    qint64 second = QDateTime(QDate(1900, 1, 1)).secsTo(QDateTime::currentDateTime());

    QByteArray request(48, 0);
    request[0] = static_cast<char>((LI << 6) | (VN << 3) | (MODE));
    request[1] = STRATUM;
    request[2] = POLL;
    request[3] = PREC;
    request[5] = 1;
    request[9] = 1;
    request[40] = static_cast<char>((second >> 24) & 0xFF);
    request[41] = static_cast<char>((second >> 16) & 0xFF);
    request[42] = static_cast<char>((second >>  8) & 0xFF);
    request[43] = static_cast<char>((second >>  0) & 0xFF);
    d_ptr->socket->write(request);
}

void HNtpClient::readData()
{
    QByteArray data;
    QDateTime epoch(QDate(1900, 1, 1));
    QDateTime unixStart(QDate(1970, 1, 1));

    while (d_ptr->socket->hasPendingDatagrams())
        data = d_ptr->socket->receiveDatagram().data();

    auto transmit = data.right(8);
    quint32 seconds = 0;

    for (int i = 0; i < 4; i++)
        seconds = seconds  * 256 + static_cast<uchar>(transmit.at(i));
    QDateTime dateTime;
    dateTime.setSecsSinceEpoch(seconds - epoch.secsTo(unixStart));
    d_ptr->socket->disconnectFromHost();
    if (dateTime.isValid())
        emit receiveTime(dateTime);
}

void HNtpClient::init()
{
    d_ptr->host = "ntp1.aliyun.com";
    d_ptr->socket = new QUdpSocket(this);
    connect(d_ptr->socket, &QUdpSocket::connected, this, &HNtpClient::sendData);
    connect(d_ptr->socket, &QUdpSocket::readyRead, this, &HNtpClient::readData);
}

HE_END_NAMESPACE
