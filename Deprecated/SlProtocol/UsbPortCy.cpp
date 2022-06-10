/////////////////////////////////////////
// 隐式间接调用
/////////////////////////////////////////
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

/////////////////////////////////////////
// 显示间接调用
/////////////////////////////////////////
//#include "UsbPortCy.h"
//#include "include/CYUSB.h"
//
//#pragma comment(lib, "lib/CYUSB.lib")
//
//CUsbPortCy::CUsbPortCy()
//{
//	_isConnected = false;
//}
//
//CUsbPortCy::~CUsbPortCy()
//{
//	if (_isConnected)
//		close();
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

/////////////////////////////////////////
// 直接调用
/////////////////////////////////////////
#include "UsbPortCy.h"
#include <windows.h>
#include "include/CyAPI.h"

#pragma comment(lib,"lib/CyAPI")

class CCyUSB
{
public:
    CCyUSB();
    ~CCyUSB();

public:
    bool Open(int nIndex = 0);
    bool Close();
    void SetTimeout(int nTime);
    int ReadData(unsigned char* pData, int nLength);
    int WriteData(unsigned char* pData, int nLength);

protected:
    CCyUSBDevice* m_pUSBDev;
    CCyBulkEndPoint* m_pReadEpt;
    CCyBulkEndPoint* m_pWriteEpt;
    int m_nTimeout;
};

CCyUSB *theCyUsb = new CCyUSB;

CCyUSB::CCyUSB()
{
    m_nTimeout = 1000;

    //  GUID guid = {0xAE18AA61, 0x7F6A, 0x11D4, 0x97, 0xDD, 0x00, 0x01, 0x02, 0x29, 0xB9, 0x58};
    //	m_pUSBDev = new CCyUSBDevice(NULL, guid);
    m_pUSBDev = new CCyUSBDevice(NULL);
    m_pReadEpt = 0;
    m_pWriteEpt = 0;
}

CCyUSB::~CCyUSB()
{
    m_pUSBDev->Close();
    if (m_pReadEpt)
        delete m_pReadEpt;
    if (m_pWriteEpt)
        delete m_pWriteEpt;
    delete m_pUSBDev;
}

bool CCyUSB::Open(int nIndex)
{
    int i;
    bool out, in, bulk;

    if (nIndex >= m_pUSBDev->DeviceCount())
        return false;

    if (!m_pUSBDev->Open(nIndex))
        return false;

    for (i = 1; i < m_pUSBDev->EndPointCount(); i++)
    {
        out = m_pUSBDev->EndPoints[i]->Address == 0x02;
        in = m_pUSBDev->EndPoints[i]->Address == 0x86;
        bulk = m_pUSBDev->EndPoints[i]->Attributes == 2;
        if (bulk && in)
        {
            m_pReadEpt = (CCyBulkEndPoint *)m_pUSBDev->EndPoints[i];
            m_pReadEpt->SetXferSize(5120);
        }
        if (bulk && out)
        {
            m_pWriteEpt = (CCyBulkEndPoint *)m_pUSBDev->EndPoints[i];
            m_pWriteEpt->SetXferSize(512);
        }
    }
    return true;
}

bool CCyUSB::Close()
{
    m_pUSBDev->Close();
    return m_pUSBDev->IsOpen();
}

void CCyUSB::SetTimeout(int nTime)
{
    m_nTimeout = nTime;
}

int CCyUSB::ReadData(unsigned char* pData, int nLength)
{
    if (m_pReadEpt == 0)
        return 0;

    long longLen = nLength;

    m_pReadEpt->TimeOut = m_nTimeout;
    if (!m_pReadEpt->XferData(pData, longLen))
        return 0;
    return longLen;
}

int CCyUSB::WriteData(unsigned char* pData, int nLength)
{
    if (m_pWriteEpt == 0)
        return 0;

    long longLen = nLength;

    m_pWriteEpt->TimeOut = m_nTimeout;
    if (!m_pWriteEpt->XferData(pData, longLen))
        return 0;
    return longLen;
}

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
    if (_isConnected || !theCyUsb->Open(num))
        return false;

    theCyUsb->SetTimeout(500);
    _isConnected = true;
    return true;
}

bool CUsbPortCy::close()
{
    if (!_isConnected || !theCyUsb->Close())
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
    return theCyUsb->WriteData(data, maxSize) == maxSize;
}

bool CUsbPortCy::read(unsigned char *data, int maxSize)
{
    return theCyUsb->ReadData(data, maxSize) == maxSize;
}
