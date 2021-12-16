#pragma once

#include "HModelSpec.h"
#include "HeController/HAbstractModel_p.h"

HE_BEGIN_NAMESPACE
class HSpecCalibrateWidget;
class ITestSpec;
HE_END_NAMESPACE

class HModelSpecPrivate : public HAbstractModelPrivate
{
public:
    HModelSpecPrivate();

public:
    HSpecCalibrateWidget *widget();

public:
    ITestSpec *testSpec = nullptr;
    HSpecCalibrateWidget *testWidget = nullptr;
};
