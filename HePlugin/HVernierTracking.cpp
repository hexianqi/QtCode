#include "HVernierTracking_p.h"
#include <QStyleOptionFocusRect>
#include <QStylePainter>
#include <QMouseEvent>

HVernierTrackingPrivate::HVernierTrackingPrivate(Qt::Orientation o, QWidget *p)
    : HAbstractVernierTrackingPrivate(o, p)
{
}

void HVernierTrackingPrivate::paintVernier()
{
    QStylePainter painter(parent);
    painter.save();
    painter.setPen(color);
    for (auto v : verniers)
    {
        if (orientation == Qt::Horizontal)
            painter.drawLine(validRegion.left() + 2, v.y(), validRegion.right() - 2, v.y());
        if (orientation == Qt::Vertical)
            painter.drawLine(v.x(), validRegion.top() + 2, v.x(), validRegion.bottom() - 2);
    }
    painter.restore();
}

HVernierTracking::HVernierTracking(Qt::Orientation orientation, QWidget *parent)
    : HAbstractVernierTracking(*new HVernierTrackingPrivate(orientation, parent), parent)
{
}

HVernierTracking::HVernierTracking(HVernierTrackingPrivate &p, QWidget *parent)
    : HAbstractVernierTracking(p, parent)
{
}

HVernierTracking::~HVernierTracking()
{
}

void HVernierTracking::paintEvent(QPaintEvent *)
{
    Q_D(HVernierTracking);
    if (!isEnable())
        return;
    d->paintVernier();
}

bool HVernierTracking::mouseMoveEvent(QMouseEvent *e)
{
    Q_D(HVernierTracking);
    auto pos = d->pos;
    if (!d->isValid(e->localPos()) || pos == -1)
        return false;

    emit vernierPosChanged(d->verniers[pos]);
    d->verniers[pos] = e->localPos();
    emit vernierPosChanged(d->verniers[pos]);
    return true;
}
