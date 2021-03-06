#include "HUsbPortCy_p.h"
#include <QtCore/QVector>
#include <QtDebug>

HE_COMMUNICATE_USE_NAMESPACE

#ifndef Q_CC_MSVC
#include <QtCore/QLibrary>
#include <QtCore/QFile>
#define Open        d->open
#define Close       d->close
#define SetTimeout  d->setTimeout
#define ReadData    d->readData
#define WriteData   d->writeData
void HUsbPortCyPrivate::loadDll()
{
    lib.reset(new QLibrary("CYUSB.dll"));
    if (!lib->load())
        return;

    open = FunOpen(lib->resolve("Open"));
    close = FunClose(lib->resolve("Close"));
    setTimeout = FunSetTimeout(lib->resolve("SetTimeout"));
    readData = FunReadData(lib->resolve("ReadData"));
    writeData = FunWriteData(lib->resolve("WriteData"));
    isLoaded = true;
}

void HUsbPortCyPrivate::unloadDLL()
{
    if (lib == nullptr)
        return;
    lib->unload();
    isLoaded = false;
}
#else
#include "include/CYUSB.h"
#include <QFile>
#pragma comment(lib, "CYUSB.lib")

void HUsbPortCyPrivate::loadDll()
{
    isLoaded = QFile::exists("CYUSB.dll");
}

void HUsbPortCyPrivate::unloadDLL()
{
    isLoaded = false;
}
#endif


HUsbPortCy::HUsbPortCy() :
    HAbstractPort(*new HUsbPortCyPrivate)
{
    Q_D(HUsbPortCy);
    d->loadDll();
}

HUsbPortCy::HUsbPortCy(HUsbPortCyPrivate &p) :
    HAbstractPort(p)
{
    Q_D(HUsbPortCy);
    d->loadDll();
}

HUsbPortCy::~HUsbPortCy()
{
    Q_D(HUsbPortCy);
    d->unloadDLL();
}

QString HUsbPortCy::typeName()
{
    return "HUsbPortCy";
}

HErrorType HUsbPortCy::openPort(int portNum)
{
    Q_D(HUsbPortCy);
    if (!d->isLoaded)
        return E_PORT_NO_DLL;
    if (!Open(portNum))
        return E_PORT_INVALID_HANDLE;
    SetTimeout(d->timeOut);
    return E_OK;
}

HErrorType HUsbPortCy::closePort()
{
    Q_D(HUsbPortCy);
    Close();
    return E_OK;
}

HErrorType HUsbPortCy::writeData(uchar *data, int maxSize)
{
    Q_D(HUsbPortCy);
    auto ret = WriteData(data, maxSize);
    if (ret < maxSize)
        return E_PORT_WRITE_DATA_LESS;
    if (ret != maxSize)
        return E_PORT_WRITE_FAILED;
    return E_OK;
}

HErrorType HUsbPortCy::readData(uchar *data, int maxSize)
{
    Q_D(HUsbPortCy);
    auto ret = ReadData(data, maxSize);
    if (ret < maxSize)
        return E_PORT_READ_DATA_LESS;
    if (ret != maxSize)
        return E_PORT_READ_FAILED;
    return E_OK;
}
