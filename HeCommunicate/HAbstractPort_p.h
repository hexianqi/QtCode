#pragma once

#include "HAbstractPort.h"

HE_COMMUNICATE_BEGIN_NAMESPACE

class HAbstractPortPrivate
{
public:
    int portNum = 1;
    int timeOut = 3000;
    bool connected = false;
};

HE_COMMUNICATE_END_NAMESPACE
