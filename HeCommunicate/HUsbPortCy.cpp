#include "HUsbPortCy_p.h"
#include "HeCore/HException.h"
#include <QtCore/QDebug>

HE_COMMUNICATE_USE_NAMESPACE

#ifndef Q_CC_MSVC
#include <QtCore/QLibrary>
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
#include <QtCore/QFile>
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
    qDebug() << __func__;
    Q_D(HUsbPortCy);
    d->unloadDLL();
}

QString HUsbPortCy::typeName()
{
    return "HUsbPortCy";
}

QString HUsbPortCy::portType()
{
    return "USB";
}

bool HUsbPortCy::openPort(int portNum)
{
    Q_D(HUsbPortCy);
    if (!d->isLoaded)
        throw HException(E_PORT_NO_DLL);
    if (!Open(portNum))
        throw HException(E_PORT_INVALID_HANDLE);
    SetTimeout(d->timeOut);
    return true;
}

bool HUsbPortCy::closePort()
{
    Q_D(HUsbPortCy);
    return Close();
}

int HUsbPortCy::writeData(uchar *data, int maxSize)
{
    Q_D(HUsbPortCy);
    return WriteData(data, maxSize);
}

int HUsbPortCy::readData(uchar *data, int maxSize)
{
    Q_D(HUsbPortCy);
    return ReadData(data, maxSize);
}
