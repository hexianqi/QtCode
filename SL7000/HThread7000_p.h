#pragma once

#include "HThread7000.h"
#include "HeController/HIntegrateThread_p.h"

class HThread7000Private : public HIntegrateThreadPrivate
{
public:
    HThread7000Private();

public:
    IProtocol *protocolKeyence = nullptr;
    IActionStrategy *strategyKeyence = nullptr;
};
