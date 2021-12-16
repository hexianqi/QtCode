#include "HUsbPortCy7c68013_p.h"
#include "include/ezusbsys.h"
#include "HeCore/HException.h"
#include <windows.h>

HE_BEGIN_NAMESPACE

HUsbPortCy7c68013::HUsbPortCy7c68013() :
    HAbstractPort(*new HUsbPortCy7c68013Private)
{
}

HUsbPortCy7c68013::HUsbPortCy7c68013(HUsbPortCy7c68013Private&p) :
    HAbstractPort(p)
{
}

HUsbPortCy7c68013::~HUsbPortCy7c68013() = default;

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

QString HUsbPortCy7c68013::portType()
{
    return "USB";
}

bool HUsbPortCy7c68013::openPort(int portNum)
{
    Q_D(HUsbPortCy7c68013);

    auto name = QString(R"(\\.\EZUSB-%1)").arg(portNum).toStdWString().c_str();
    d->handle = CreateFileW(name, GENERIC_READ | GENERIC_WRITE, 0, nullptr, OPEN_EXISTING, d->isAsync ? FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED : 0, nullptr);
    if (d->handle == INVALID_HANDLE_VALUE)
        throw HException(E_PORT_INVALID_HANDLE);
    return true;
}

bool HUsbPortCy7c68013::closePort()
{
    Q_D(HUsbPortCy7c68013);
    return CloseHandle(d->handle);
}

int HUsbPortCy7c68013::writeData(uchar *data, int maxSize)
{
    Q_D(HUsbPortCy7c68013);

    auto ret = 0ul;
    auto pipeNum = 0ul;
    if (d->isAsync)
    {
        OVERLAPPED os;
        if (!DeviceIoControl(d->handle, IOCTL_EZUSB_BULK_WRITE, &pipeNum, sizeof(ulong), data, maxSize, &ret, &os))
        {
            if (GetLastError() == ERROR_IO_PENDING)
                GetOverlappedResult(d->handle, &os, &ret, true);
            else
                throw HException(E_PORT_WRITE_FAILED);
        }
    }
    else
    {
        if (!DeviceIoControl(d->handle, IOCTL_EZUSB_BULK_WRITE, &pipeNum, sizeof(ulong), data, maxSize, &ret, nullptr))
            throw HException(E_PORT_WRITE_FAILED);
    }
    return ret;
}

int HUsbPortCy7c68013::readData(uchar *data, int maxSize)
{
    Q_D(HUsbPortCy7c68013);

    auto ret = 0ul;
    auto pipeNum = 2ul;
    if (d->isAsync)
    {
        OVERLAPPED os;
        if (!DeviceIoControl(d->handle, IOCTL_EZUSB_BULK_READ, &pipeNum, sizeof(ulong), data, maxSize, &ret, &os))
        {
            if (GetLastError() == ERROR_IO_PENDING)
                GetOverlappedResult(d->handle, &os, &ret, true);
            else
                throw HException(E_PORT_READ_FAILED);
        }
    }
    else
    {
        if (!DeviceIoControl(d->handle, IOCTL_EZUSB_BULK_READ, &pipeNum, sizeof(ulong), data, maxSize, &ret, nullptr))
            throw HException(E_PORT_READ_FAILED);
    }
    return ret;
}

HE_END_NAMESPACE
