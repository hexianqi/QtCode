#pragma once

#include "HThread7000.h"
#include "HeController/HAbstractThread_p.h"

HE_BEGIN_NAMESPACE
class ITestData;
HE_END_NAMESPACE

class HThread7000Private : public HAbstractThreadPrivate
{
public:
    HThread7000Private();

public:
    ITestData *testData = nullptr;
    IProtocol *protocolSpec = nullptr;
    IProtocol *protocolElse = nullptr;
    IActionStrategy *strategySpec = nullptr;
    IActionStrategy *strategyElec = nullptr;
    IActionStrategy *strategyLuminous = nullptr;
};
