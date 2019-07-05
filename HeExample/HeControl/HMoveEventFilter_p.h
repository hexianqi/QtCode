#ifndef HMOVEEVENTFILTER_P_H
#define HMOVEEVENTFILTER_P_H

#include "HMoveEventFilter.h"
#include "HAbstractMouseEventFilter_p.h"

HE_CONTROL_BEGIN_NAMESPACE

class HMoveEventFilterPrivate : public HAbstractMouseEventFilterPrivate
{
public:
    using HAbstractMouseEventFilterPrivate::HAbstractMouseEventFilterPrivate;

public:
    bool pressed = false;
    QPoint pos;
};

HE_CONTROL_END_NAMESPACE

#endif // HMOVEEVENTFILTER_P_H
