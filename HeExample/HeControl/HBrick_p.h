#pragma once

#include "HBrick.h"
#include "HGameObject_p.h"

HE_CONTROL_BEGIN_NAMESPACE

class HBrickPrivate : public HGameObjectPrivate
{
public:
    bool solid = false;
    bool destroyed = false;
};

HE_CONTROL_END_NAMESPACE

