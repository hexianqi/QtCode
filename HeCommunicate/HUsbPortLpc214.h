#ifndef HUSBPORTLPC214_H
#define HUSBPORTLPC214_H

#include "HAbstractPort.h"

HE_COMMUNICATE_BEGIN_NAMESPACE

class HUsbPortLpc214Private;

class HUsbPortLpc214 : public HAbstractPort
{
    Q_DECLARE_PRIVATE(HUsbPortLpc214)

public:
    explicit HUsbPortLpc214();
    ~HUsbPortLpc214();

public:
    virtual QString typeName() override;

protected:
    HUsbPortLpc214(HUsbPortLpc214Private &p);

protected:
    virtual HErrorType openPort(int portNum) override;
    virtual HErrorType closePort() override;
    virtual HErrorType writeData(uchar *data, int maxSize) override;
    virtual HErrorType readData(uchar *data, int maxSize) override;
};

HE_COMMUNICATE_END_NAMESPACE

#endif // HUSBPORTLPC214_H
