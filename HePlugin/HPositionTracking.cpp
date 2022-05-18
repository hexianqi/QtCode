#include "HPositionTracking_p.h"
#include <QtGui/QMouseEvent>
#include <QtWidgets/QWidget>

HPositionTrackingPrivate::HPositionTrackingPrivate(QWidget *p) :
    HAbstractMouseStrategyPrivate(p)
{
    p->setMouseTracking(true);
}

HPositionTracking::HPositionTracking(QWidget *parent) :
    HAbstractMouseStrategy(*new HPositionTrackingPrivate(parent), parent)
{
}

HPositionTracking::HPositionTracking(HPositionTrackingPrivate &p, QWidget *parent) :
    HAbstractMouseStrategy(p, parent)
{
}

bool HPositionTracking::mousePressEvent(QMouseEvent *)
{
    return true;
}

bool HPositionTracking::mouseMoveEvent(QMouseEvent *event)
{
    if (!isValid(event->localPos()))
        return false;
    emit positionChanged(event->localPos());
    return true;
}

bool HPositionTracking::mouseReleaseEvent(QMouseEvent *)
{
    return true;
}
