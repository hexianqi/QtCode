#include "HSerialPort_p.h"
#include "HeCore/HException.h"
#include <windows.h>
#include <QtCore/QDebug>

HE_COMMUNICATE_BEGIN_NAMESPACE

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
        setBaudRate(param.value("baudRate").toUInt());
}

QString HSerialPort::typeName()
{
    return "HSerialPort";
}

QString HSerialPort::portType()
{
    return "COM";
}

void HSerialPort::setBaudRate(ulong value)
{
    Q_D(HSerialPort);
    d->baudRate = value;
}

bool HSerialPort::openPort(int portNum)
{
    Q_D(HSerialPort);

    DCB dcb;
    auto name = QString("COM%1").arg(portNum).toStdWString().c_str();
    COMMTIMEOUTS timeOuts;
    timeOuts.ReadIntervalTimeout = 0;
    timeOuts.ReadTotalTimeoutMultiplier = 2;
    timeOuts.ReadTotalTimeoutConstant = ulong(d->timeOut);
    timeOuts.WriteTotalTimeoutMultiplier = 2;
    timeOuts.WriteTotalTimeoutConstant = ulong(d->timeOut);

    d->handle = CreateFileW(name, GENERIC_READ|GENERIC_WRITE, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
    if (d->handle == INVALID_HANDLE_VALUE)
        throw HException(E_PORT_INVALID_HANDLE);

    try
    {
        SetupComm(d->handle, 10240, 10240);
        SetCommTimeouts(d->handle, &timeOuts);
        if (!GetCommState(d->handle, &dcb))
            throw HException(E_PORT_INVALID_HANDLE);
        dcb.BaudRate = d->baudRate;
        dcb.ByteSize = 8;
        dcb.StopBits = 0;
        dcb.fParity = 1;
        dcb.fBinary = 1;
        dcb.Parity = 0;
        if (!SetCommState(d->handle, &dcb))
            throw HException(E_PORT_INVALID_HANDLE);
        return true;
    }
    catch (HException &e)
    {
        closePort();
        e.raise();
        return false;
    }
}

bool HSerialPort::closePort()
{
    Q_D(HSerialPort);
    return CloseHandle(d->handle);
}

int HSerialPort::writeData(uchar *buff, int size)
{
    Q_D(HSerialPort);
    ulong ret;

//    FlushFileBuffers(d->hDevice);
    PurgeComm(d->handle, PURGE_TXCLEAR);
    PurgeComm(d->handle, PURGE_RXCLEAR);
    if (!WriteFile(d->handle, buff, size, &ret, nullptr))
        throw HException(E_PORT_WRITE_FAILED);
    return ret;
}

int HSerialPort::readData(uchar *buff, int size)
{
    Q_D(HSerialPort);
    ulong ret;

    if (!ReadFile(d->handle, buff, size, &ret, nullptr))
        throw HException(E_PORT_READ_FAILED);
    return ret;
}

HE_COMMUNICATE_END_NAMESPACE
