#include "HUsbPortLpc214_p.h"
#include "HeCore/HException.h"

HE_USE_NAMESPACE

#ifndef Q_CC_MSVC
#include <QtCore/QLibrary>
#define ReadData214x    d->readData
#define WriteData214x   d->writeData

void HUsbPortLpc214Private::loadDll()
{
    lib.reset(new QLibrary("EasyUSB214x.dll"));
    if (!lib->load())
        return;

    writeData = Fun(lib->resolve("WriteData214x"));
    readData = Fun(lib->resolve("ReadData214x"));
    isLoaded = true;
}

void HUsbPortLpc214Private::unloadDLL()
{
    if (lib == nullptr)
        return;
    lib->unload();
    isLoaded = false;
}
#else
#include "include/EasyUSB214x.h"
#include <QtCore/QFile>
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

HUsbPortLpc214::HUsbPortLpc214(QObject *parent) :
    HAbstractPort(*new HUsbPortLpc214Private, parent)
{
    Q_D(HUsbPortLpc214);
    d->loadDll();
}

HUsbPortLpc214::HUsbPortLpc214(HUsbPortLpc214Private &p, QObject *parent) :
    HAbstractPort(p, parent)
{
    Q_D(HUsbPortLpc214);
    d->loadDll();
}

HUsbPortLpc214::~HUsbPortLpc214()
{
    Q_D(HUsbPortLpc214);
    d->unloadDLL();
}

QString HUsbPortLpc214::typeName()
{
    return "HUsbPortLpc214";
}

QString HUsbPortLpc214::portType()
{
    return "USB";
}

bool HUsbPortLpc214::openPort(int /*portNum*/)
{
    return true;
}

bool HUsbPortLpc214::closePort()
{
    return true;
}

int HUsbPortLpc214::writeData(uchar *data, int maxSize)
{
    Q_D(HUsbPortLpc214);
    return WriteData214x(1, data, maxSize, d->timeOut);
}

int HUsbPortLpc214::readData(uchar *data, int maxSize)
{
    Q_D(HUsbPortLpc214);
    return ReadData214x(2, data, maxSize, d->timeOut);
}
