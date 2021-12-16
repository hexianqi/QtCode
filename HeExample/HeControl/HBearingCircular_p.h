#pragma once

#include "HBearingCircular.h"
#include "HAbstractCircular_p.h"

HE_BEGIN_NAMESPACE

class HBearingCircularPrivate : public HAbstractCircularPrivate
{
public:
    QColor background = QColor(46, 194, 163);
    QColor foreground = QColor(255, 107, 107);
};

HE_END_NAMESPACE
