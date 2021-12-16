#pragma once

#include "HThread2100DC.h"
#include "HeController/HAbstractThread_p.h"

HE_BEGIN_NAMESPACE
class ITestData;
HE_END_NAMESPACE

class HThread2100DCPrivate : public HAbstractThreadPrivate
{
public:
    HThread2100DCPrivate();

public:
    ITestData *testData = nullptr;
    IProtocol *protocolSpec = nullptr;
    IProtocol *protocolElec = nullptr;
    IActionStrategy *strategySpec = nullptr;
    IActionStrategy *strategyElec = nullptr;
};



