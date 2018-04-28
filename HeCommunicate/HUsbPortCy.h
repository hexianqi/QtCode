#ifndef HUSBPORTCY_H
#define HUSBPORTCY_H

#include "HAbstractPort.h"

HE_COMMUNICATE_BEGIN_NAMESPACE

class HUsbPortCyPrivate;

class HUsbPortCy : public HAbstractPort
{
    Q_DECLARE_PRIVATE(HUsbPortCy)

public:
    explicit HUsbPortCy(QObject *parent = nullptr);
    ~HUsbPortCy();

protected:
    HUsbPortCy(HUsbPortCyPrivate &p, QObject *parent = nullptr);

protected:
    virtual HErrorType openPort(int portNum) override;
    virtual HErrorType closePort() override;
    virtual HErrorType writeData(uchar *data, int maxSize) override;
    virtual HErrorType readData(uchar *data, int maxSize) override;
};

HE_COMMUNICATE_END_NAMESPACE

#endif // HUSBPORTCY_H
