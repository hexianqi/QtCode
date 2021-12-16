#pragma once

#include "HSpecCalibrate.h"

HE_BEGIN_NAMESPACE

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

HE_END_NAMESPACE
