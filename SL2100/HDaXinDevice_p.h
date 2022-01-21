#pragma once

#include "HDaXinDevice.h"
#include "HeCommunicate/HAbstractDevice_p.h"

class HDaXinDevicePrivate : public HAbstractDevicePrivate
{
public:
    HDaXinDevicePrivate();

public:
    uchar da;
    uchar sa;
};
