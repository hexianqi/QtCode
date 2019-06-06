#ifndef HABSTRACTMOUSEEVENTFILTER_P_H
#define HABSTRACTMOUSEEVENTFILTER_P_H

#include "HAbstractMouseEventFilter.h"
#include <QtCore/QRectF>

HE_CONTROL_BEGIN_NAMESPACE

class HAbstractMouseEventFilterPrivate
{
public:
    HAbstractMouseEventFilterPrivate(QWidget *p);

public:
    QWidget *parent = nullptr;
    QRectF validRegion;
    bool enable = true;
};

HE_CONTROL_END_NAMESPACE

#endif // HABSTRACTMOUSEEVENTFILTER_P_H
