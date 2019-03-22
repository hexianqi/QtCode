/***************************************************************************************************
**      2018-06-19  HUsbPortCy USB端口类。
***************************************************************************************************/

#ifndef HUSBPORTCY_H
#define HUSBPORTCY_H

#include "HAbstractPort.h"

HE_COMMUNICATE_BEGIN_NAMESPACE

class HUsbPortCyPrivate;

class HUsbPortCy : public HAbstractPort
{
    Q_DECLARE_PRIVATE(HUsbPortCy)

public:
    explicit HUsbPortCy();
    ~HUsbPortCy() override;

public:
    QString typeName() override;

protected:
    HUsbPortCy(HUsbPortCyPrivate &);

protected:
    HErrorType openPort(int portNum) override;
    HErrorType closePort() override;
    HErrorType writeData(uchar *data, int maxSize) override;
    HErrorType readData(uchar *data, int maxSize) override;
};

HE_COMMUNICATE_END_NAMESPACE

#endif // HUSBPORTCY_H
