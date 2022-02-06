#pragma once

#include "HThread2000AC.h"
#include "HeController/HAbstractThread_p.h"

class HThread2000ACPrivate : public HAbstractThreadPrivate
{
public:
    HThread2000ACPrivate();

public:    
    IProtocol *protocolSpec = nullptr;
    IProtocol *protocolElec = nullptr;
    IActionStrategy *strategySpec = nullptr;
    IActionStrategy *strategyElec = nullptr;
};
