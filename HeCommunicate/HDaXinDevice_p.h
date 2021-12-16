#pragma once

#include "HDaXinDevice.h"
#include "HAbstractDevice_p.h"

HE_BEGIN_NAMESPACE

class HDaXinDevicePrivate : public HAbstractDevicePrivate
{
public:
    HDaXinDevicePrivate();

public:
    uchar da;
    uchar sa;
};

HE_END_NAMESPACE
