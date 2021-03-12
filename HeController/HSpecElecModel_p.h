#pragma once

#include "HSpecElecModel.h"
#include "HAbstractModel_p.h"

HE_DATA_BEGIN_NAMESPACE
class ITestData;
class ITestSpec;
HE_DATA_END_NAMESPACE

HE_CONTROLLER_BEGIN_NAMESPACE

class HSpecElecModelPrivate : public HAbstractModelPrivate
{
public:
    HSpecElecModelPrivate();

public:
    ITestData *testElec = nullptr;
    ITestSpec *testSpec = nullptr;
};

HE_CONTROLLER_END_NAMESPACE
