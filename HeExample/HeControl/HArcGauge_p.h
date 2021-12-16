#pragma once

#include "HArcGauge.h"
#include "HCircleGauge_p.h"

HE_BEGIN_NAMESPACE

class HArcGaugePrivate : public HCircleGaugePrivate
{
public:
    HArcGaugePrivate();

public:
    QColor arcColor = QColor(50, 50, 50);
    HControlType::PointerStyle pointerStyle = HControlType::PointerStyle_Circle;
};

HE_END_NAMESPACE
