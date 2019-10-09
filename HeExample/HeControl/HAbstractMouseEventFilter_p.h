#ifndef HABSTRACTMOUSEEVENTFILTER_P_H
#define HABSTRACTMOUSEEVENTFILTER_P_H

#include "HAbstractMouseEventFilter.h"
#include "HAbstractEventFilter_p.h"

HE_CONTROL_BEGIN_NAMESPACE

class HAbstractMouseEventFilterPrivate : public HAbstractEventFilterPrivate
{
public:
    HAbstractMouseEventFilterPrivate(QWidget *p);

public:
    QWidget *parent = nullptr;
};

HE_CONTROL_END_NAMESPACE

#endif // HABSTRACTMOUSEEVENTFILTER_P_H
