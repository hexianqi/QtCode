#pragma once

#include "HIntegrateThread.h"
#include "HAbstractThread_p.h"

HE_BEGIN_NAMESPACE

class HE_CONTROLLER_EXPORT HIntegrateThreadPrivate : public HAbstractThreadPrivate
{
public:
    HIntegrateThreadPrivate();

public:
    IProtocol *protocolSpec = nullptr;
    IProtocol *protocolElse = nullptr;
    IActionStrategy *strategySpec = nullptr;
    IActionStrategy *strategyElec = nullptr;
    IActionStrategy *strategyLuminous = nullptr;
    IActionStrategy *strategyMotor = nullptr;
};

HE_END_NAMESPACE

