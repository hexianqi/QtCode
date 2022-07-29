#pragma once

#include "HTestThread.h"

class HTestThreadPrivate
{
public:
    HTestThreadPrivate();


public:
    volatile bool running = false;
    int index;
};



