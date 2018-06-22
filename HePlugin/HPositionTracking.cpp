#include "HPositionTracking_p.h"
#include <QLabel>
#include <QMouseEvent>

HPositionTrackingPrivate::HPositionTrackingPrivate(QWidget *p)
    : HAbstractMouseStrategyPrivate(p)
{
    label = new QLabel(parent);
    label->setAlignment(Qt::AlignLeft | Qt::AlignBottom);
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

void HPositionTracking::setValidRegion(QRectF value)
{
    Q_D(HPositionTracking);
    d->label->setGeometry(value.left() + 10, value.top() + 10, value.width() - 20, d->label->fontMetrics().height());
    HAbstractMouseStrategy::setValidRegion(value);
}

void HPositionTracking::setEnable(bool b)
{
    Q_D(HPositionTracking);
    d->label->setVisible(b);
    HAbstractMouseStrategy::setEnable(b);
}

void HPositionTracking::setText(QString text)
{
    Q_D(HPositionTracking);
    d->label->setText(text);
}

void HPositionTracking::paintEvent(QPaintEvent *)
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
