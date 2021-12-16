#pragma once

#include "HUsbPortCy7c68013.h"
#include "HAbstractPort_p.h"

HE_BEGIN_NAMESPACE

class HUsbPortCy7c68013Private : public HAbstractPortPrivate
{
public:
    void *handle = nullptr;
    bool isAsync = false;
};

HE_END_NAMESPACE
