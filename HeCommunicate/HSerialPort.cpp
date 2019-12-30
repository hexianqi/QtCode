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

HErrorType HSerialPort::openPort(int port)
{
    Q_D(HSerialPort);
    if (d->connected)
        return E_PORT_OPENED;

    DCB dcb;
    auto name = QString("COM%1").arg(port).toStdWString().c_str();
    COMMTIMEOUTS timeOuts;
    timeOuts.ReadIntervalTimeout = 0;
    timeOuts.ReadTotalTimeoutMultiplier = 1;
    timeOuts.ReadTotalTimeoutConstant = 300;
    timeOuts.WriteTotalTimeoutMultiplier = 1;
    timeOuts.WriteTotalTimeoutConstant = 300;

    d->hDevice = CreateFileW(name, GENERIC_READ|GENERIC_WRITE, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
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
    auto num = static_cast<ulong>(size);

//    FlushFileBuffers(d->hDevice);
    PurgeComm(d->hDevice, PURGE_TXCLEAR);
    PurgeComm(d->hDevice, PURGE_RXCLEAR);
    if (!WriteFile(d->hDevice, buff, num, &ret, nullptr))
        return E_PORT_WRITE_FAILED;
    if (ret < num)
        return E_PORT_WRITE_DATA_LESS;
    return E_OK;
}

HErrorType HSerialPort::readData(uchar *buff, int size)
{
    Q_D(HSerialPort);
    ulong ret;
    auto num = static_cast<ulong>(size);

    if (!ReadFile(d->hDevice, buff, num, &ret, nullptr))
        return E_PORT_READ_FAILED;
    if (ret < num)
        return E_PORT_READ_DATA_LESS;
    return E_OK;
}

HE_COMMUNICATE_END_NAMESPACE
