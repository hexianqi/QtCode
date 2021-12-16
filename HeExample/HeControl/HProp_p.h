#pragma once

#include "HProp.h"
#include "HGameObject_p.h"

HE_BEGIN_NAMESPACE

class HPropPrivate : public HGameObjectPrivate
{
public:
    QString type;
    float duration = 0.0f;
    bool activated = false;
    bool destroyed = false;
};

HE_END_NAMESPACE

