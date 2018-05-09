#ifndef HDEVICESL_P_H
#define HDEVICESL_P_H

#include "HAbstractDevice_p.h"
#include "HDeviceSL.h"
#include <QVector>

HE_COMMUNICATE_BEGIN_NAMESPACE

class HDeviceSLPrivate : public HAbstractDevicePrivate
{
public:
    HDeviceSLPrivate();

public:
    void setEncrypt(QVector<bool> value);
    void setCheckCode(QVector<bool> value);
    bool isEncrypt(int n);
    bool isCheckCode(int n);

public:
    QVector<bool> encrypts;
    QVector<bool> checkCodes;
};

HE_COMMUNICATE_END_NAMESPACE

#endif // HPROTOCOLSTRATEGYSL_P_H
