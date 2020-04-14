#include "HUsbPortCy7c68013_p.h"
#include "include/ezusbsys.h"
#include <QtCore/QDebug>
#include <windows.h>

HE_COMMUNICATE_BEGIN_NAMESPACE

HUsbPortCy7c68013::HUsbPortCy7c68013() :
    HAbstractPort(*new HUsbPortCy7c68013Private)
{
}

HUsbPortCy7c68013::HUsbPortCy7c68013(HUsbPortCy7c68013Private&p) :
    HAbstractPort(p)
{
}

HUsbPortCy7c68013::~HUsbPortCy7c68013()
{
    qDebug() << __func__;
    close();
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

    auto name = QString(R"(\\.\EZUSB-%1)").arg(portNum).toStdWString().c_str();
    d->handle = CreateFileW(name, GENERIC_READ | GENERIC_WRITE, 0, nullptr, OPEN_EXISTING, d->isAsync ? FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED : 0, nullptr);
    if (d->handle == INVALID_HANDLE_VALUE)
        return E_PORT_INVALID_HANDLE;
    return E_OK;
}

HErrorType HUsbPortCy7c68013::closePort()
{
    Q_D(HUsbPortCy7c68013);
    CloseHandle(d->handle);
    return E_OK;
}

HErrorType HUsbPortCy7c68013::writeData(uchar *data, int maxSize)
{
    Q_D(HUsbPortCy7c68013);

    auto ret = 0ul;
    auto pipeNum = 0ul;
    auto size = ulong(maxSize);
    if (d->isAsync)
    {
        OVERLAPPED os;
        if (!DeviceIoControl(d->handle, IOCTL_EZUSB_BULK_WRITE, &pipeNum, sizeof(ulong), data, size, &ret, &os))
        {
            if (GetLastError() == ERROR_IO_PENDING)
                GetOverlappedResult(d->handle, &os, &ret, true);
            else
                return E_PORT_WRITE_FAILED;
        }
    }
    else
    {
        if (!DeviceIoControl(d->handle, IOCTL_EZUSB_BULK_WRITE, &pipeNum, sizeof(ulong), data, size, &ret, nullptr))
            return E_PORT_WRITE_FAILED;
    }
    if (ret < size)
        return E_PORT_WRITE_DATA_LESS;
    return E_OK;
}

HErrorType HUsbPortCy7c68013::readData(uchar *data, int maxSize)
{
    Q_D(HUsbPortCy7c68013);

    auto ret = 0ul;
    auto pipeNum = 2ul;
    auto size = ulong(maxSize);
    if (d->isAsync)
    {
        OVERLAPPED os;
        if (!DeviceIoControl(d->handle, IOCTL_EZUSB_BULK_READ, &pipeNum, sizeof(ulong), data, size, &ret, &os))
        {
            if (GetLastError() == ERROR_IO_PENDING)
                GetOverlappedResult(d->handle, &os, &ret, true);
            else
                return E_PORT_READ_FAILED;
        }
    }
    else
    {
        if (!DeviceIoControl(d->handle, IOCTL_EZUSB_BULK_READ, &pipeNum, sizeof(ulong), data, size, &ret, nullptr))
            return E_PORT_READ_FAILED;
    }
    if (ret < size)
        return E_PORT_READ_DATA_LESS;
    return E_OK;
}

HE_COMMUNICATE_END_NAMESPACE
