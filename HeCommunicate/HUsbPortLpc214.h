/***************************************************************************************************
**      2018-06-19  HUsbPortLpc214 USB端口类。
***************************************************************************************************/

#pragma once

#include "HAbstractPort.h"

HE_BEGIN_NAMESPACE

class HUsbPortLpc214Private;

class HUsbPortLpc214 : public HAbstractPort
{
    Q_DECLARE_PRIVATE(HUsbPortLpc214)

public:
    explicit HUsbPortLpc214();
    ~HUsbPortLpc214() override;

public:
    QString typeName() override;
    QString portType() override;

protected:
    HUsbPortLpc214(HUsbPortLpc214Private &);

protected:
    bool openPort(int portNum) override;
    bool closePort() override;
    int writeData(uchar *data, int maxSize) override;
    int readData(uchar *data, int maxSize) override;
};

HE_END_NAMESPACE
