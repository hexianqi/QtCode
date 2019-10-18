#ifndef HSPECCALIBRATE_P_H
#define HSPECCALIBRATE_P_H

#include "HSpecCalibrate.h"

HE_DATA_BEGIN_NAMESPACE

class IDataFactory;
class HSpecSetting;
class HSpecStdCurve;
class HSpecPelsWave;
class HSpecLuminous;

class HSpecCalibratePrivate
{
public:
    HSpecCalibratePrivate();

public:
    IDataFactory *factory = nullptr;
    HSpecSetting *setting;
    HSpecFitting *fitting;
    HSpecStdCurve *stdCurve;
    HSpecPelsWave *pelsWave;
    HSpecLuminous *luminous;
};

HE_DATA_END_NAMESPACE

#endif // HSPECCALIBRATE_P_H
