#pragma once

#include "HSpecElecThread.h"
#include "HAbstractThread_p.h"
#include "HeData/HDataGlobal.h"

HE_DATA_BEGIN_NAMESPACE
class ITestData;
HE_DATA_END_NAMESPACE
HE_DATA_USE_NAMESPACE

HE_CONTROLLER_BEGIN_NAMESPACE

class HSpecElecThreadPrivate : public HAbstractThreadPrivate
{
public:
    HSpecElecThreadPrivate();

public:
    IProtocol *protocolSpec = nullptr;
    IProtocol *protocolElse = nullptr;
    ITestData *testData = nullptr;
    IActionStrategy *strategySpec = nullptr;
    IActionStrategy *strategyElec = nullptr;
};

HE_CONTROLLER_END_NAMESPACE
