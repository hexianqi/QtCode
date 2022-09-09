#include "HUsbPortCy.h"

#ifndef Q_CC_MSVC
HUsbPortCy::HUsbPortCy()
{
    _isConnected = false;
    loadDll();
}

HUsbPortCy::~HUsbPortCy()
{
    if (_isConnected)
        close();
    unloadDLL();
}

bool HUsbPortCy::open(int num)
{
    if (!_isLoaded || _isConnected)
        return false;
    if (!Open(num))
        return false;;
    SetTimeout(2000);
    _isConnected = true;
    return true;
}

bool HUsbPortCy::close()
{
    if (!_isConnected)
        return true;
    if (!Close())
        return false;
    _isConnected = false;
    return true;
}

bool HUsbPortCy::write(vector<unsigned char> data)
{
    return write(&data[0], data.size());
}

bool HUsbPortCy::write(unsigned char *data, int maxSize)
{
    return WriteData(data, maxSize);
}

bool HUsbPortCy::read(vector<unsigned char> &data)
{
    return read(&data[0], data.size());
}

bool HUsbPortCy::read(unsigned char *data, int maxSize)
{
    return ReadData(data, maxSize);
}

bool HUsbPortCy::sn(vector<wchar_t> &data)
{
    return true;
//    return Sn(&data[0], data.size());
}

bool HUsbPortCy::transport(vector<unsigned char> downData, vector<unsigned char> &upData)
{
    return true;
//    return Transport(&downData[0], downData.size(), &upData[0], upData.size());
}

bool HUsbPortCy::writeX(vector<unsigned char> downData, vector<unsigned char> &upData)
{
    return true;
//    return WriteX(&downData[0], downData.size(), &upData[0], upData.size());
}

bool HUsbPortCy::readX(vector<unsigned char> &data)
{
    return true;
//    return ReadX(&data[0], data.size());
}

bool HUsbPortCy::isReadyX()
{
    return true;
//    return IsReadyX();
}

void HUsbPortCy::loadDll()
{
    _dll = LoadLibrary("CYUSB.dll");
    if (_dll == NULL)
        FreeLibrary(_dll);

    Open = FunOpen(GetProcAddress(_dll, "Open"));
    Close = FunClose(GetProcAddress(_dll, "Close"));
    SetTimeout = FunSetTimeout(GetProcAddress(_dll, "SetTimeout"));
    ReadData = FunReadData(GetProcAddress(_dll, "ReadData"));
    WriteData = FunWriteData(GetProcAddress(_dll, "WriteData"));
    _isLoaded = true;
}

void HUsbPortCy::unloadDLL()
{
    FreeLibrary(_dll);
    _isLoaded = false;
}

#else

#include "CCyUSB.h"

HUsbPortCy::HUsbPortCy()
{
    _usb = new CCyUSB;
    _isConnected = false;
}

HUsbPortCy::~HUsbPortCy()
{
    if (_isConnected)
        close();
    delete _usb;
}

bool HUsbPortCy::open(int num)
{
    if (_isConnected || !_usb->open(num))
        return false;

    _usb->setTimeout(2000);
    _isConnected = true;
    return true;
}

bool HUsbPortCy::close()
{
    if (!_isConnected)
        return true;
    if (!_usb->close())
        return false;
    _isConnected = false;
    return true;
}

bool HUsbPortCy::write(vector<unsigned char> data)
{
    return write(&data[0], data.size());
}

bool HUsbPortCy::write(unsigned char *data, int maxSize)
{
    return _usb->write(data, maxSize) == maxSize;
}

bool HUsbPortCy::read(vector<unsigned char> &data)
{
    return read(&data[0], data.size());
}

bool HUsbPortCy::read(unsigned char *data, int maxSize)
{
    return _usb->read(data, maxSize) == maxSize;
}

bool HUsbPortCy::sn(vector<wchar_t> &data)
{
    return _usb->sn(&data[0], data.size());
}

bool HUsbPortCy::transport(vector<unsigned char> downData, vector<unsigned char> &upData)
{
    return _usb->transport(&downData[0], downData.size(), &upData[0], upData.size());
}

bool HUsbPortCy::writeX(vector<unsigned char> downData, vector<unsigned char> &upData)
{
    return _usb->writeX(&downData[0], downData.size(), &upData[0], upData.size());
}

bool HUsbPortCy::readX(vector<unsigned char> &data)
{
    return _usb->readX(&data[0], data.size());
}

bool HUsbPortCy::isReadyX()
{
    return _usb->isReadyX();
}

#endif
