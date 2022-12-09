#pragma once

#include "HThread1000RGB.h"
#include "HeController/HAbstractThread_p.h"

class HThread1000RGBPrivate : public HAbstractThreadPrivate
{
public:
    HThread1000RGBPrivate();

public:
    IProtocol *protocolSpec = nullptr;
    IProtocol *protocolElse = nullptr;
    IActionStrategy *strategySpec = nullptr;
    IActionStrategy *strategyElec = nullptr;
    IActionStrategy *strategyLuminous = nullptr;
};



