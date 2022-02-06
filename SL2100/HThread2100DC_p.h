#pragma once

#include "HThread2100DC.h"
#include "HeController/HAbstractThread_p.h"

class HThread2100DCPrivate : public HAbstractThreadPrivate
{
public:
    HThread2100DCPrivate();

public:
    IProtocol *protocolSpec = nullptr;
    IProtocol *protocolElec = nullptr;
    IActionStrategy *strategySpec = nullptr;
    IActionStrategy *strategyElec = nullptr;
};



