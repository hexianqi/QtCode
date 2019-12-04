#include "HUsbPortCy7c68013_p.h"
#include "include/ezusbsys.h"
#include <QtCore/QDebug>
#include <windows.h>

HE_COMMUNICATE_BEGIN_NAMESPACE

HUsbPortCy7c68013::HUsbPortCy7c68013()
    : HAbstractPort(*new HUsbPortCy7c68013Private)
{
}

HUsbPortCy7c68013::HUsbPortCy7c68013(HUsbPortCy7c68013Private&p)
    : HAbstractPort(p)
{
}

HUsbPortCy7c68013::~HUsbPortCy7c68013()
{
    qDebug() << __func__;
}

void HUsbPortCy7c68013::initialize(QVariantMap param)
{
    Q_D(HUsbPortCy7c68013);
    HAbstractPort::initialize(param);
    if (param.contains("async"))
        d->isAsync = param.value("async").toBool();
}

QString HUsbPortCy7c68013::typeName()
{
    return "HUsbPortCy7c68013";
}

HErrorType HUsbPortCy7c68013::openPort(int portNum)
{
    Q_D(HUsbPortCy7c68013);

    wchar_t ch[64] = L"";
    QString("\\\\.\\EZUSB-%1").arg(portNum).toWCharArray(ch);

    DWORD flags = d->isAsync ? FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED : 0;
    d->hand = CreateFileW(ch, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, flags, NULL);
    if (d->hand == INVALID_HANDLE_VALUE)
        return E_PORT_INVALID_HANDLE;

    return E_OK;
}

HErrorType HUsbPortCy7c68013::closePort()
{
    Q_D(HUsbPortCy7c68013);
    CloseHandle(d->hand);
    return E_OK;
}

HErrorType HUsbPortCy7c68013::writeData(uchar *data, int maxSize)
{
    Q_D(HUsbPortCy7c68013);

    ulong ret;
    ulong pipeNum = 0;
    if (d->isAsync)
    {
        OVERLAPPED os;
        if (!DeviceIoControl(d->hand, IOCTL_EZUSB_BULK_WRITE, &pipeNum, sizeof(ulong), data, maxSize, &ret, &os))
        {
            if (GetLastError() == ERROR_IO_PENDING)
                GetOverlappedResult(d->hand, &os, &ret, true);
            else
                return E_PORT_WRITE_FAILED;
        }
    }
    else
    {
        if (!DeviceIoControl(d->hand, IOCTL_EZUSB_BULK_WRITE, &pipeNum, sizeof(ulong), data, maxSize, &ret, NULL))
            return E_PORT_WRITE_FAILED;
    }
    if (ret < static_cast<ulong>(maxSize))
        return E_PORT_WRITE_DATA_LESS;
    return E_OK;
}

HErrorType HUsbPortCy7c68013::readData(uchar *data, int maxSize)
{
    Q_D(HUsbPortCy7c68013);

    ulong ret;
    ulong pipeNum = 2;
    if (d->isAsync)
    {
        OVERLAPPED os;
        if (!DeviceIoControl(d->hand, IOCTL_EZUSB_BULK_READ, &pipeNum, sizeof(ulong), data, maxSize, &ret, &os))
        {
            if (GetLastError() == ERROR_IO_PENDING)
                GetOverlappedResult(d->hand, &os, &ret, true);
            else
                return E_PORT_READ_FAILED;
        }
    }
    else
    {
        if (!DeviceIoControl(d->hand, IOCTL_EZUSB_BULK_READ, &pipeNum, sizeof(ulong), data, maxSize, &ret, NULL))
            return E_PORT_READ_FAILED;
    }
    if (ret < static_cast<ulong>(maxSize))
        return E_PORT_READ_DATA_LESS;
    return E_OK;
}

HE_COMMUNICATE_END_NAMESPACE
