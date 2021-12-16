#pragma once

#include "HSpecElecModel.h"
#include "HAbstractModel_p.h"

HE_BEGIN_NAMESPACE

class ITestData;
class ITestSpec;

class HSpecElecModelPrivate : public HAbstractModelPrivate
{
public:
    HSpecElecModelPrivate();

public:
    ITestData *testElec = nullptr;
    ITestSpec *testSpec = nullptr;
};

HE_END_NAMESPACE
