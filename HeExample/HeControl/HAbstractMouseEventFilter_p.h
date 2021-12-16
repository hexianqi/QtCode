#pragma once

#include "HAbstractMouseEventFilter.h"
#include "HAbstractEventFilter_p.h"
#include <QtCore/QPoint>

HE_BEGIN_NAMESPACE

class HAbstractMouseEventFilterPrivate : public HAbstractEventFilterPrivate
{
public:
    bool pressed = false;
    QPoint lastPos;
};

HE_END_NAMESPACE
