#ifndef HCIRCLEZOOMCIRCULAR_P_H
#define HCIRCLEZOOMCIRCULAR_P_H

#include "HCircleZoomCircular.h"
#include "HAbstractCircular_p.h"

HE_CONTROL_BEGIN_NAMESPACE

class HZoomCircleCircularPrivate : public HAbstractCircularPrivate
{
public:
    QColor foreground = QColor(46, 194, 163);
    int minimum = 10;
    bool bounce = false;
};

HE_CONTROL_END_NAMESPACE

#endif // HZOOMCIRCLECIRCULAR_P_H
