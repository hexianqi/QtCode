#pragma once

#include "HSpecElecThread.h"
#include "HAbstractThread_p.h"

HE_BEGIN_NAMESPACE

class ITestData;

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

HE_END_NAMESPACE
