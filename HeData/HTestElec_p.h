#ifndef HTESTELEC_P_H
#define HTESTELEC_P_H

#include "HTestElec.h"
#include "HTestData_p.h"

HE_DATA_BEGIN_NAMESPACE

class IElecCalibrate;

class HTestElecPrivate : public HTestDataPrivate
{
public:
    IElecCalibrateCollection *collection = nullptr;
    IElecCalibrate *calibrate = nullptr;
    int module = 0;
    QMap<HElecType, int> gears;
};

HE_DATA_END_NAMESPACE

#endif // HTESTELEC_P_H
