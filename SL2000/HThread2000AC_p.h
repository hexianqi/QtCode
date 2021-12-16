#pragma once

#include "HThread2000AC.h"
#include "HeController/HAbstractThread_p.h"

HE_BEGIN_NAMESPACE
class ITestData;
HE_END_NAMESPACE

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
