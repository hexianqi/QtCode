#pragma once

#include "HTestSetWidget7000.h"
#include "HeGui/HAbstractTestSetWidget_p.h"

class HTestSetWidget7000Private : public HAbstractTestSetWidgetPrivate
{
public:
    QPolygon polygon;
    bool autoIntegralTime = false;
    bool autoLuminousGears = true;
    bool prepare = false;
};
