#pragma once

#include "HThread2100DC.h"
#include "HeController/HAbstractThread_p.h"
#include "HeData/HDataGlobal.h"

HE_DATA_BEGIN_NAMESPACE
class ITestData;
HE_DATA_END_NAMESPACE
HE_DATA_USE_NAMESPACE

class HThread2100DCPrivate : public HAbstractThreadPrivate
{
public:
    HThread2100DCPrivate();

public:
    ITestData *testData = nullptr;
    IProtocol *protocolSpec = nullptr;
    IProtocol *protocolElec = nullptr;
    IProtocol *protocolElse = nullptr;
    IActionStrategy *strategySpec = nullptr;
    IActionStrategy *strategyElec = nullptr;
    IActionStrategy *strategyElse = nullptr;
};



