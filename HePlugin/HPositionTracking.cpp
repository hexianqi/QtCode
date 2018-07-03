#include "HPositionTracking_p.h"
#include "IPositionTrackingControl.h"
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

void HPositionTracking::setControl(IPositionTrackingControl *p)
{
    Q_D(HPositionTracking);
    d->control = p;
}

void HPositionTracking::setValidRegion(QRectF value)
{
    Q_D(HPositionTracking);
    d->control->setValidRegion(value);
    HAbstractMouseStrategy::setValidRegion(value);
}

void HPositionTracking::setEnable(bool b)
{
    Q_D(HPositionTracking);
    d->control->setVisible(b);
    HAbstractMouseStrategy::setEnable(b);
}

void HPositionTracking::setText(QString text)
{
    Q_D(HPositionTracking);
    d->control->setText(text);
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
