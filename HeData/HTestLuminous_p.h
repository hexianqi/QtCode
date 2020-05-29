#pragma once

#include "HTestLuminous.h"
#include "HTestData_p.h"

HE_DATA_BEGIN_NAMESPACE

class ILuminousCalibrate;

class HTestLuminousPrivate : public HTestDataPrivate
{
public:
    HTestLuminousPrivate();

public:
    ILuminousCalibrateCollection *collection = nullptr;
    ILuminousCalibrate *calibrate = nullptr;
};

HE_DATA_END_NAMESPACE

