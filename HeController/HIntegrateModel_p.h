#pragma once

#include "HIntegrateModel.h"
#include "HAbstractModel_p.h"

HE_BEGIN_NAMESPACE

class ITestData;
class ITestSpec;

class HE_CONTROLLER_EXPORT HIntegrateModelPrivate : public HAbstractModelPrivate
{
public:
    HIntegrateModelPrivate();

public:
    ITestData *testElec = nullptr;
    ITestData *testLuminous = nullptr;
    ITestSpec *testSpec = nullptr;
};

HE_END_NAMESPACE

