#pragma once

#include "HIntegrateThread.h"
#include "HAbstractThread_p.h"

HE_BEGIN_NAMESPACE

class ITestData;

class HIntegrateThreadPrivate : public HAbstractThreadPrivate
{
public:
    HIntegrateThreadPrivate();

public:
    ITestData *testData = nullptr;
    IProtocol *protocolSpec = nullptr;
    IProtocol *protocolElse = nullptr;
    IActionStrategy *strategySpec = nullptr;
    IActionStrategy *strategyElec = nullptr;
    IActionStrategy *strategyLuminous = nullptr;
};

HE_END_NAMESPACE

