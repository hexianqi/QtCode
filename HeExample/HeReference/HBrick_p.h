#pragma once

#include "HBrick.h"
#include "HGameObject_p.h"

HE_REFERENCE_BEGIN_NAMESPACE

class HBrickPrivate : public HGameObjectPrivate
{
public:
    bool solid = false;
    bool destroyed = false;
};

HE_REFERENCE_END_NAMESPACE

