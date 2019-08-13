//#include "UsbPortCy.h"
//
//CUsbPortCy::CUsbPortCy()
//{
//	_isConnected = false;
//	loadDll();
//}
//
//CUsbPortCy::~CUsbPortCy()
//{
//	if (_isConnected)
//		close();
//	unloadDLL();
//}
//
//bool CUsbPortCy::open(int num)
//{
//	if (_isConnected || !Open(num))
//		return false;
//
//	SetTimeout(500);
//	_isConnected = true;
//	return true;
//}
//
//bool CUsbPortCy::close()
//{
//	if (!_isConnected || !Close())
//		return false;
//	_isConnected = false;
//	return true;
//}
//
//bool CUsbPortCy::write(vector<unsigned char> data)
//{
//	return write(data.data(), data.size());
//}
//
//bool CUsbPortCy::read(vector<unsigned char> &data)
//{
//	return read(data.data(), data.size());
//}
//
//bool CUsbPortCy::write(unsigned char *data, int maxSize)
//{
//	return WriteData(data, maxSize) == maxSize;
//}
//
//bool CUsbPortCy::read(unsigned char *data, int maxSize)
//{
//	return ReadData(data, maxSize) == maxSize;
//}
//
//void CUsbPortCy::loadDll()
//{
//	_hdll = LoadLibrary(L"CYUSB.dll");
//	if (_hdll == NULL)
//	{
//		FreeLibrary(_hdll);
//		return;
//	}
//	Open = (FunOpen)GetProcAddress(_hdll, "Open");
//	Close = (FunClose)GetProcAddress(_hdll, "Close");
//	SetTimeout = (FunSetTimeout)GetProcAddress(_hdll, "SetTimeout");
//	ReadData = (FunReadData)GetProcAddress(_hdll, "ReadData");
//	WriteData = (FunWriteData)GetProcAddress(_hdll, "WriteData");
//	_isLoaded = true;
//}
//
//void CUsbPortCy::unloadDLL()
//{
//	if (_isLoaded)
//	{
//		FreeLibrary(_hdll);
//		_isLoaded = false;
//	}
//}

#include "UsbPortCy.h"
#include "include/CYUSB.h"

#pragma comment(lib, "lib/CYUSB.lib")

CUsbPortCy::CUsbPortCy()
{
    _isConnected = false;
}

CUsbPortCy::~CUsbPortCy()
{
    if (_isConnected)
        close();
}

bool CUsbPortCy::open(int num)
{
    if (_isConnected || !Open(num))
        return false;

    SetTimeout(500);
    _isConnected = true;
    return true;
}

bool CUsbPortCy::close()
{
    if (!_isConnected || !Close())
        return false;
    _isConnected = false;
    return true;
}

bool CUsbPortCy::write(vector<unsigned char> data)
{
    return write(data.data(), data.size());
}

bool CUsbPortCy::read(vector<unsigned char> &data)
{
    return read(data.data(), data.size());
}

bool CUsbPortCy::write(unsigned char *data, int maxSize)
{
    return WriteData(data, maxSize) == maxSize;
}

bool CUsbPortCy::read(unsigned char *data, int maxSize)
{
    return ReadData(data, maxSize) == maxSize;
}
