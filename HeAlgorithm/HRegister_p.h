#ifndef HREGISTER_P_H
#define HREGISTER_P_H

#include "HRegister.h"
#include <QString>

HE_ALGORITHM_BEGIN_NAMESPACE

class HRegisterPrivate
{
public:
    QString registerId;
    QString serialNumber;
    int trialTimes;
    int firstDate;
};

HE_ALGORITHM_END_NAMESPACE

#endif // HREGISTER_P_H
