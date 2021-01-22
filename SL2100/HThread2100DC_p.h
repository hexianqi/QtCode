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
    IProtocol *protocolSpec = nullptr;
    IProtocol *protocolElse = nullptr;
    ITestData *testData = nullptr;
    IActionStrategy *strategySpec = nullptr;
    IActionStrategy *strategyElec = nullptr;
};



