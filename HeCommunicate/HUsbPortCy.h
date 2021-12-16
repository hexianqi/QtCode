/***************************************************************************************************
**      2018-06-19  HUsbPortCy USB端口类。
***************************************************************************************************/

#pragma once

#include "HAbstractPort.h"

HE_BEGIN_NAMESPACE

class HUsbPortCyPrivate;

class HUsbPortCy : public HAbstractPort
{
    Q_DECLARE_PRIVATE(HUsbPortCy)

public:
    explicit HUsbPortCy();
    ~HUsbPortCy() override;

public:
    QString typeName() override;
    QString portType() override;

protected:
    HUsbPortCy(HUsbPortCyPrivate &);

protected:
    bool openPort(int portNum) override;
    bool closePort() override;
    int writeData(uchar *data, int maxSize) override;
    int readData(uchar *data, int maxSize) override;
};

HE_END_NAMESPACE
