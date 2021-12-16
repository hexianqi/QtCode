#pragma once

#include "HTestElec.h"
#include "HTestData_p.h"

HE_BEGIN_NAMESPACE

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

HE_END_NAMESPACE
