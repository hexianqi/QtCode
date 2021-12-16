#pragma once

#include "HTestLuminous.h"
#include "HTestData_p.h"

HE_BEGIN_NAMESPACE

class ILuminousCalibrate;
class ILuminousCalibrateCollection;

class HTestLuminousPrivate : public HTestDataPrivate
{
public:
    HTestLuminousPrivate();

public:
    ILuminousCalibrateCollection *collection = nullptr;
    ILuminousCalibrate *calibrate = nullptr;
};

HE_END_NAMESPACE

