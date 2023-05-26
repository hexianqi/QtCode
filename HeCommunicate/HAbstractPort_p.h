#pragma once

#include "HAbstractPort.h"

HE_BEGIN_NAMESPACE

class HAbstractPortPrivate
{
public:
    int timeOut = 3000;
    bool connected = false;
};

HE_END_NAMESPACE
