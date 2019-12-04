#ifndef HABSTRACTEVENTFILTER_P_H
#define HABSTRACTEVENTFILTER_P_H

#include "HAbstractEventFilter.h"
#include <QtCore/QRectF>
#include <QtCore/QHash>

HE_CONTROL_BEGIN_NAMESPACE

class HAbstractEventFilterPrivate
{
public:
    QRectF validRegion;
    bool enable = true;
    QHash<QEvent::Type, std::function<bool(QEvent *)>> handleFunc;
};

HE_CONTROL_END_NAMESPACE

#endif // HABSTRACTEVENTFILTER_P_H
