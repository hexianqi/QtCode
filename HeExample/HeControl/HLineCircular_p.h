#pragma once

#include "HLineCircular.h"
#include "HAbstractCircular_p.h"

HE_BEGIN_NAMESPACE

class HLineCircularPrivate : public HAbstractCircularPrivate
{
public:
    QColor foreground = QColor(46, 194, 163);
};

HE_END_NAMESPACE
