#pragma once

#include "HConfig.h"

#ifdef Q_CC_MSVC
#include <windows.h>
#include "include/cyapi.h"

#pragma comment(lib, "CyAPI.lib")

class CCyUSB
{
public:
    CCyUSB();
    ~CCyUSB();

public:
    bool open(int index = 0);
    bool close();
    void setTimeout(int value);
    int read(unsigned char *data, int length);
    int write(unsigned char *data, int length);
    bool sn(wchar_t *data, int length);
    bool transport(unsigned char *downData, long downLength, unsigned char *upData, long upLength);
    bool writeX(unsigned char *downData, long downLength, unsigned char *upData, long upLength);
    bool readX(unsigned char *data, long length);
    bool isReadyX();

protected:
    CCyUSBDevice *_device;
    CCyBulkEndPoint *_readEpt;
    CCyBulkEndPoint *_writeEpt;
    int _timeout;
    OVERLAPPED _outOverlapped;
    OVERLAPPED _inOverlapped;
    UCHAR *_outContext;
    UCHAR *_inContext;
};

#endif
