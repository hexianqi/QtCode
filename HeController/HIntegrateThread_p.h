#pragma once

#include "HIntegrateThread.h"
#include "HAbstractThread_p.h"
#include "HeData/HDataGlobal.h"

HE_DATA_BEGIN_NAMESPACE
class ITestData;
HE_DATA_END_NAMESPACE
HE_DATA_USE_NAMESPACE

HE_CONTROLLER_BEGIN_NAMESPACE

class HIntegrateThreadPrivate : public HAbstractThreadPrivate
{
public:
    HIntegrateThreadPrivate();

public:
    IProtocol *protocolSpec = nullptr;
    IProtocol *protocolElse = nullptr;
    ITestData *testData = nullptr;
    IActionStrategy *strategySpec = nullptr;
    IActionStrategy *strategyElec = nullptr;
    IActionStrategy *strategyLuminous = nullptr;
};

HE_CONTROLLER_END_NAMESPACE

