#include "HUsbPortLpc214_p.h"

HE_COMMUNICATE_USE_NAMESPACE

#ifndef Q_CC_MSVC
#include <QLibrary>
#define ReadData214x    d->readData
#define WriteData214x   d->writeData

void HUsbPortLpc214Private::loadDll()
{
    lib = new QLibrary("EasyUSB214x.dll");
    if (!lib->load())
        return;

    writeData = (Fn)lib->resolve("WriteData214x");
    readData = (Fn)lib->resolve("ReadData214x");

    isLoaded = true;
}

void HUsbPortLpc214Private::unloadDLL()
{
    if (lib == nullptr)
        return;
    lib->unload();
    isLoaded = false;
    delete lib;
}
#else
#include "include/EasyUSB214x.h"
#include <QFile>
#pragma comment(lib, "EasyUSB214x.lib")

void HUsbPortLpc214Private::loadDll()
{
    isLoaded = QFile::exists("EasyUSB214x.dll");
}

void HUsbPortLpc214Private::unloadDLL()
{
    isLoaded = false;
}
#endif

HUsbPortLpc214::HUsbPortLpc214(QObject *parent)
    : HAbstractPort(*new HUsbPortLpc214Private(), parent)
{
    Q_D(HUsbPortLpc214);
    d->loadDll();
}

HUsbPortLpc214::HUsbPortLpc214(HUsbPortLpc214Private &p, QObject *parent)
    : HAbstractPort(p, parent)
{
    Q_D(HUsbPortLpc214);
    d->loadDll();
}

HUsbPortLpc214::~HUsbPortLpc214()
{
    Q_D(HUsbPortLpc214);
    d->unloadDLL();
}

HErrorType HUsbPortLpc214::openPort(int portNum)
{
    Q_UNUSED(portNum)
    return E_OK;
}

HErrorType HUsbPortLpc214::closePort()
{
    return E_OK;
}

HErrorType HUsbPortLpc214::writeData(uchar *data, int maxSize)
{
    Q_D(HUsbPortLpc214);
    auto ret = WriteData214x(1, data, maxSize, d->timeOut);
    if (ret < maxSize)
        return E_PORT_WRITE_DATA_LESS;
    if (ret != maxSize)
        return E_PORT_WRITE_FAILED;
    return E_OK;
}

HErrorType HUsbPortLpc214::readData(uchar *data, int maxSize)
{
    Q_D(HUsbPortLpc214);
    auto ret = ReadData214x(2, data, maxSize, d->timeOut);
    if (ret < maxSize)
        return E_PORT_READ_DATA_LESS;
    if (ret != maxSize)
        return E_PORT_READ_FAILED;
    return E_OK;
}
