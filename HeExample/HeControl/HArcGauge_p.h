#ifndef HARCGAUGE_P_H
#define HARCGAUGE_P_H

#include "HArcGauge.h"
#include "HCircleGauge_p.h"

HE_CONTROL_BEGIN_NAMESPACE

class HArcGaugePrivate : public HCircleGaugePrivate
{
public:
    HArcGaugePrivate();

public:
    QColor arcColor = QColor(50, 50, 50);    
    PointerStyle pointerStyle = PointerStyle_Circle;
};

HE_CONTROL_END_NAMESPACE

#endif // HARCGAUGE_P_H
