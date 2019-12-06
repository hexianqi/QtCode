#include "HSerialPort_p.h"
#include <QtSerialPort/QSerialPort>
#include <QtCore/QDebug>

HE_COMMUNICATE_BEGIN_NAMESPACE

HSerialPortPrivate::HSerialPortPrivate() :
    port(new QSerialPort)
{
}

HSerialPort::HSerialPort() :
    HAbstractPort(*new HSerialPortPrivate)
{
}

HSerialPort::HSerialPort(HSerialPortPrivate &p) :
    HAbstractPort(p)
{
}

HSerialPort::~HSerialPort()
{
    qDebug() << __func__;
}

void HSerialPort::initialize(QVariantMap param)
{
    HAbstractPort::initialize(param);
    if (param.contains("baudRate"))
        setBaudRate(param.value("baudRate").toInt());
}

QString HSerialPort::typeName()
{
    return "HSerialPort";
}

HErrorType HSerialPort::transport(QVector<uchar> &downData, QVector<uchar> &upData, int delay)
{
    Q_D(HSerialPort);
    auto error = write(downData);
    if (error != E_OK)
        return error;

    if (delay > 10)
        d->port->waitForReadyRead(delay);

    return read(upData);
}

HErrorType HSerialPort::clear()
{
    if (!isConnected())
        return E_PORT_CLOSED;

    Q_D(HSerialPort);
    d->port->clear();
    return E_OK;
}

void HSerialPort::setBaudRate(int value)
{
    Q_D(HSerialPort);
    d->baudRate = value;
}

HErrorType HSerialPort::openPort(int portNum)
{
    Q_D(HSerialPort);
    if (d->port->isOpen())
        d->port->close();
    d->port->setPortName(QString("COM%1").arg(portNum));
    d->port->setBaudRate(d->baudRate);
    if (!d->port->open(QIODevice::ReadWrite))
        return E_PORT_INVALID_HANDLE;
    return E_OK;
}

HErrorType HSerialPort::closePort()
{
    Q_D(HSerialPort);
    d->port->close();
    return E_OK;
}

HErrorType HSerialPort::writeData(uchar *data, int maxSize)
{
    Q_D(HSerialPort);
    auto ret = d->port->write(reinterpret_cast<char *>(data), maxSize);
    if(!d->port->waitForBytesWritten(d->timeOut))
        return E_PORT_WRITE_FAILED;
    if (ret < maxSize)
        return E_PORT_WRITE_DATA_LESS;
    return E_OK;

}
HErrorType HSerialPort::readData(uchar *data, int maxSize)
{
    Q_D(HSerialPort);

    if (!d->port->waitForReadyRead(d->timeOut))
        return E_PORT_READ_FAILED;
    auto ret = d->port->read(reinterpret_cast<char *>(data), maxSize);
    if (ret < maxSize)
        return E_PORT_READ_DATA_LESS;
    return E_OK;
}

HE_COMMUNICATE_END_NAMESPACE
