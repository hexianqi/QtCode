#include "HPositionTracking_p.h"
#include <QMouseEvent>

HPositionTrackingPrivate::HPositionTrackingPrivate(QWidget *p)
    : HAbstractMouseStrategyPrivate(p)
{
}

HPositionTracking::HPositionTracking(QWidget *parent)
    : HAbstractMouseStrategy(*new HPositionTrackingPrivate(parent), parent)
{
}

HPositionTracking::HPositionTracking(HPositionTrackingPrivate &p, QWidget *parent)
    : HAbstractMouseStrategy(p, parent)
{
}

HPositionTracking::~HPositionTracking()
{
}

bool HPositionTracking::mousePressEvent(QMouseEvent *)
{
    return true;
}

bool HPositionTracking::mouseMoveEvent(QMouseEvent *e)
{
    Q_D(HPositionTracking);
    if (!d->isValid(e->localPos()))
        return false;
    emit positionChanged(e->localPos());
    return true;
}

bool HPositionTracking::mouseReleaseEvent(QMouseEvent *)
{
    return true;
}
