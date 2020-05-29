#pragma once

#include "HIntegrateModel.h"
#include "HAbstractModel_p.h"

HE_DATA_BEGIN_NAMESPACE
class ITestSpec;
class ITestElec;
class ITestLuminous;
HE_DATA_END_NAMESPACE

HE_CONTROLLER_BEGIN_NAMESPACE

class HIntegrateModelPrivate : public HAbstractModelPrivate
{
public:
    HIntegrateModelPrivate();

public:
    ITestSpec *testSpec = nullptr;
    ITestElec *testElec = nullptr;
    ITestLuminous *testLuminous = nullptr;
};

HE_CONTROLLER_END_NAMESPACE

