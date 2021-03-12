/***************************************************************************************************
**      2018-06-19  HUsbPortCy7c68013 USB端口类。
***************************************************************************************************/

#pragma once

#include "HAbstractPort.h"

HE_COMMUNICATE_BEGIN_NAMESPACE

class HUsbPortCy7c68013Private;

class HUsbPortCy7c68013 : public HAbstractPort
{
    Q_DECLARE_PRIVATE(HUsbPortCy7c68013)

public:
    explicit HUsbPortCy7c68013();
    ~HUsbPortCy7c68013() override;

public:
    void initialize(QVariantMap param) override;
    QString typeName() override;
    QString portType() override;

protected:
    HUsbPortCy7c68013(HUsbPortCy7c68013Private &);

protected:
    bool openPort(int portNum) override;
    bool closePort() override;
    int writeData(uchar *data, int maxSize) override;
    int readData(uchar *data, int maxSize) override;
};

HE_COMMUNICATE_END_NAMESPACE
