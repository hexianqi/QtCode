#pragma once

#include "HBall.h"
#include "HGameObject_p.h"

HE_BEGIN_NAMESPACE

class HBallPrivate : public HGameObjectPrivate
{
public:
    float radius = 12.5f;
    bool stuck = true;
    bool sticky = false;
    bool passThrough = false;
};

HE_END_NAMESPACE

