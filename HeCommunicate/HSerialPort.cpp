#include "HSerialPort_p.h"
#include <QtCore/QDebug>
#include <windows.h>

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

void HSerialPort::setBaudRate(ulong value)
{
    Q_D(HSerialPort);
    d->baudRate = value;
}

HErrorType HSerialPort::openPort(int portNum)
{
    Q_D(HSerialPort);
    if (d->connected)
        return E_PORT_OPENED;

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
        return E_PORT_INVALID_HANDLE;

    SetupComm(d->handle, 10240, 10240);
    SetCommTimeouts(d->handle, &timeOuts);

    if (!GetCommState(d->handle, &dcb))
    {
        CloseHandle(d->handle);
        return E_PORT_INVALID_HANDLE;
    }
    dcb.BaudRate = d->baudRate;
    dcb.ByteSize = 8;
    dcb.StopBits = 0;
    dcb.fParity = 1;
    dcb.fBinary = 1;
    dcb.Parity = 0;
    if (!SetCommState(d->handle, &dcb))
    {
        CloseHandle(d->handle);
        return E_PORT_INVALID_HANDLE;
    }
    return E_OK;
}

HErrorType HSerialPort::closePort()
{
    Q_D(HSerialPort);
    CloseHandle(d->handle);
    return E_OK;
}

HErrorType HSerialPort::writeData(uchar *buff, int size)
{
    Q_D(HSerialPort);
    ulong ret;
    auto num = ulong(size);

//    FlushFileBuffers(d->hDevice);
    PurgeComm(d->handle, PURGE_TXCLEAR);
    PurgeComm(d->handle, PURGE_RXCLEAR);
    if (!WriteFile(d->handle, buff, num, &ret, nullptr))
        return E_PORT_WRITE_FAILED;
    if (ret < num)
        return E_PORT_WRITE_DATA_LESS;
    return E_OK;
}

HErrorType HSerialPort::readData(uchar *buff, int size)
{
    Q_D(HSerialPort);
    ulong ret;
    auto num = ulong(size);

    if (!ReadFile(d->handle, buff, num, &ret, nullptr))
        return E_PORT_READ_FAILED;
    if (ret < num)
        return E_PORT_READ_DATA_LESS;
    return E_OK;
}

HE_COMMUNICATE_END_NAMESPACE
