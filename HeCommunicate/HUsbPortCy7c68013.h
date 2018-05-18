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
    ~HUsbPortCy7c68013();

public:
    virtual void initialize(QVariantMap param) override;
    virtual QString typeName() override;

protected:
    HUsbPortCy7c68013(HUsbPortCy7c68013Private &p);

protected:
    virtual HErrorType openPort(int portNum) override;
    virtual HErrorType closePort() override;
    virtual HErrorType writeData(uchar *data, int maxSize) override;
    virtual HErrorType readData(uchar *data, int maxSize) override;
};

HE_COMMUNICATE_END_NAMESPACE

#endif // HUSBPORTCY7C68013_H
