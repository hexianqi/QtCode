#pragma once

#include "HZoomCircleCircular.h"
#include "HAbstractCircular_p.h"

HE_BEGIN_NAMESPACE

class HZoomCircleCircularPrivate : public HAbstractCircularPrivate
{
public:
    QColor foreground = QColor(46, 194, 163);
    int minimum = 10;
    bool bounce = true;
};

HE_END_NAMESPACE
