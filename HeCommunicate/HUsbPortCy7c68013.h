/***************************************************************************************************
**      2018-06-19  HUsbPortCy7c68013 USB端口类。
***************************************************************************************************/

#ifndef HUSBPORTCY7C68013_H
#define HUSBPORTCY7C68013_H

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
    HErrorType openPort(int portNum) override;
    HErrorType closePort() override;
    HErrorType writeData(uchar *data, int maxSize) override;
    HErrorType readData(uchar *data, int maxSize) override;
};

HE_COMMUNICATE_END_NAMESPACE

#endif // HUSBPORTCY7C68013_H
