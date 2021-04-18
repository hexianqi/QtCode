#pragma once

#include "HThread2000AC.h"
#include "HeController/HAbstractThread_p.h"
#include "HeData/HDataGlobal.h"

HE_DATA_BEGIN_NAMESPACE
class ITestData;
HE_DATA_END_NAMESPACE
HE_DATA_USE_NAMESPACE

class HThread2000ACPrivate : public HAbstractThreadPrivate
{
public:
    HThread2000ACPrivate();

public:
    ITestData *testData = nullptr;
    IProtocol *protocolSpec = nullptr;
    IProtocol *protocolElec = nullptr;
    IActionStrategy *strategySpec = nullptr;
    IActionStrategy *strategyElec = nullptr;
};
