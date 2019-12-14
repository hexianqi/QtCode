#include "HSerialPort_p.h"
#include <QtCore/QVector>
#include <QtSerialPort/QSerialPort>
#include <windows.h>

HE_COMMUNICATE_BEGIN_NAMESPACE

//bool HSerialPortPrivate::openSerialPort(int portNum)
//{
//    serial.reset(new QSerialPort(QString("COM%1").arg(portNum)));
//    return serial->setBaudRate(baudRate) && serial->open(QIODevice::ReadWrite);
//}

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

void HSerialPort::setBaudRate(int value)
{
    Q_D(HSerialPort);
    d->baudRate = value;
}

HErrorType HSerialPort::openPort(int port)
{
    Q_D(HSerialPort);
    if (d->connected)
        return E_PORT_OPENED;

    wchar_t ch[64] = L"";
    COMMTIMEOUTS timeOuts;
    DCB dcb;

    QString("COM%1").arg(port).toWCharArray(ch);
    timeOuts.ReadIntervalTimeout = 0;
    timeOuts.ReadTotalTimeoutMultiplier = 1;
    timeOuts.ReadTotalTimeoutConstant = 300;
    timeOuts.WriteTotalTimeoutMultiplier = 1;
    timeOuts.WriteTotalTimeoutConstant = 300;

    d->hDevice = CreateFileW(ch, GENERIC_READ|GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
    if (d->hDevice == INVALID_HANDLE_VALUE)
        return E_PORT_INVALID_HANDLE;

    SetupComm(d->hDevice, 10240, 10240);
    SetCommTimeouts(d->hDevice, &timeOuts);

    if (!GetCommState(d->hDevice, &dcb))
    {
        CloseHandle(d->hDevice);
        return E_PORT_INVALID_HANDLE;
    }
    dcb.BaudRate = d->baudRate;
    dcb.ByteSize = 8;
    dcb.StopBits = 0;
    dcb.fParity = 1;
    dcb.fBinary = 1;
    dcb.Parity = 0;
    if (!SetCommState(d->hDevice, &dcb))
    {
        CloseHandle(d->hDevice);
        return E_PORT_INVALID_HANDLE;
    }

    d->connected = true;
    clear();
    return E_OK;
}

HErrorType HSerialPort::closePort()
{
    Q_D(HSerialPort);
    if (!d->connected)
        return E_PORT_CLOSED;

    d->connected = false;
    CloseHandle(d->hDevice);
    return E_OK;
}

HErrorType HSerialPort::writeData(uchar *buff, int size)
{
    Q_D(HSerialPort);
    ulong ret;

//    FlushFileBuffers(d->hDevice);
    PurgeComm(d->hDevice, PURGE_TXCLEAR);
    PurgeComm(d->hDevice, PURGE_RXCLEAR);
    if (!WriteFile(d->hDevice, buff, size, &ret, NULL))
        return E_PORT_WRITE_FAILED;
    if (ret < size)
        return E_PORT_WRITE_DATA_LESS;

    return E_OK;
}

HErrorType HSerialPort::readData(uchar *buff, int size)
{
    Q_D(HSerialPort);
    ulong ret;

    if (!ReadFile(d->hDevice, buff, size, &ret, NULL))
        return E_PORT_READ_FAILED;
    if (ret < size)
        return E_PORT_READ_DATA_LESS;

    return E_OK;
}



//HErrorType HSerialPort::transport(QVector<uchar> &downData, QVector<uchar> &upData, int delay)
//{
//    Q_D(HSerialPort);
//    auto error = write(downData);
//    if (error != E_OK)
//        return error;

//    if (delay > 10)
//        d->serial->waitForReadyRead(delay);

//    return read(upData);
//}

//HErrorType HSerialPort::clear()
//{
//    if (!isConnected())
//        return E_PORT_CLOSED;

//    Q_D(HSerialPort);
//    d->serial->clear();
//    return E_OK;
//}

//void HSerialPort::setBaudRate(int value)
//{
//    Q_D(HSerialPort);
//    d->baudRate = value;
//}

//HErrorType HSerialPort::openPort(int portNum)
//{
//    Q_D(HSerialPort);
//    if (!d->openSerialPort(portNum))
//        return E_PORT_INVALID_HANDLE;
//    return E_OK;
//}

//HErrorType HSerialPort::closePort()
//{
//    Q_D(HSerialPort);
//    d->serial->close();
//    return E_OK;
//}

//HErrorType HSerialPort::writeData(uchar *data, int maxSize)
//{
//    Q_D(HSerialPort);
//    auto ret = d->serial->write(reinterpret_cast<char *>(data), maxSize);
//    if(!d->serial->waitForBytesWritten(d->timeOut))
//        return E_PORT_WRITE_FAILED;
//    if (ret < maxSize)
//        return E_PORT_WRITE_DATA_LESS;
//    return E_OK;

//}
//HErrorType HSerialPort::readData(uchar *data, int maxSize)
//{
//    Q_D(HSerialPort);

//    if (!d->serial->waitForReadyRead(d->timeOut))
//        return E_PORT_READ_FAILED;
//    auto ret = d->serial->read(reinterpret_cast<char *>(data), maxSize);
//    if (ret < maxSize)
//        return E_PORT_READ_DATA_LESS;
//    return E_OK;
//}

HE_COMMUNICATE_END_NAMESPACE
