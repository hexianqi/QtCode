#pragma once

#include "HIntegrateModel.h"
#include "HAbstractModel_p.h"

HE_DATA_BEGIN_NAMESPACE
class ITestData;
class ITestSpec;
HE_DATA_END_NAMESPACE

HE_CONTROLLER_BEGIN_NAMESPACE

class HIntegrateModelPrivate : public HAbstractModelPrivate
{
public:
    HIntegrateModelPrivate();

public:
    ITestData *testElec = nullptr;
    ITestData *testLuminous = nullptr;
    ITestSpec *testSpec = nullptr;
};

HE_CONTROLLER_END_NAMESPACE

