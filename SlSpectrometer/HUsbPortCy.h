#pragma once

#include "HConfig.h"
#include <vector>

// #define Q_CC_MSVC

#ifndef Q_CC_MSVC
#include <windows.h>
#else
class CCyUSB;
#endif

using namespace std;

class HUsbPortCy
{
public:
    HUsbPortCy();
    ~HUsbPortCy();

public:
    bool open(int num);
    bool close();
    bool write(vector<unsigned char> data);
    bool write(unsigned char *data, int maxSize);
    bool read(vector<unsigned char> &data);
    bool read(unsigned char *data, int maxSize);
    bool sn(vector<wchar_t> &data);
    bool transport(vector<unsigned char> downData, vector<unsigned char> &upData);
    bool writeX(vector<unsigned char> downData, vector<unsigned char> &upData);
    bool readX(vector<unsigned char> &data);
    bool isReadyX();

protected:
    bool _isConnected;

#ifndef Q_CC_MSVC
protected:
    void loadDll();
    void unloadDLL();

    using FunOpen = bool(*)(int);
    using FunClose = bool(*)();
    using FunSetTimeout = bool(*)(int);
    using FunReadData = int(*)(unsigned char *, int);
    using FunWriteData = int(*)(unsigned char *, int);

    FunOpen Open;
    FunClose Close;
    FunSetTimeout SetTimeout;
    FunReadData ReadData;
    FunWriteData WriteData;
    HINSTANCE _dll;
    bool _isLoaded;
#else
    CCyUSB *_usb;
#endif
};
