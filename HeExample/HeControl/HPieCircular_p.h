#pragma once

#include "HPieCircular.h"
#include "HAbstractCircular_p.h"

HE_CONTROL_BEGIN_NAMESPACE

class HPieCircularPrivate : public HAbstractCircularPrivate
{
public:
    QColor background = QColor(97, 117, 118);
    QColor foreground = QColor(46, 194, 163);
    int spanAngle = 60;
};

HE_CONTROL_END_NAMESPACE
