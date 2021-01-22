#ifndef HTESTELEC_P_H
#define HTESTELEC_P_H

#include "HTestElec.h"
#include "HTestData_p.h"

HE_DATA_BEGIN_NAMESPACE

class IElecCalibrate;
class IElecCalibrateCollection;

class HTestElecPrivate : public HTestDataPrivate
{
public:
    HTestElecPrivate();

public:
    IElecCalibrateCollection *collection = nullptr;
    IElecCalibrate *calibrate = nullptr;
    QMap<HElecType, int> gears;
    QMap<HElecType, double> values;
};

HE_DATA_END_NAMESPACE

#endif // HTESTELEC_P_H
