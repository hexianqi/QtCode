#include "HVernierTracking_p.h"
#include <QtGui/QMouseEvent>
#include <QtWidgets/QStyleOptionFocusRect>
#include <QtWidgets/QStylePainter>

HVernierTrackingPrivate::HVernierTrackingPrivate(Qt::Orientation o, QWidget *p)
    : HAbstractVernierTrackingPrivate(o, p)
{
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
    QStylePainter painter(d->parent);
    painter.save();
    painter.setPen(d->color);
    for (auto v : d->verniers)
    {
        if (d->orientation == Qt::Horizontal)
            painter.drawLine(d->validRegion.left() + 2, v.y(), d->validRegion.right() - 2, v.y());
        if (d->orientation == Qt::Vertical)
            painter.drawLine(v.x(), d->validRegion.top() + 2, v.x(), d->validRegion.bottom() - 2);
    }
    painter.restore();
}

bool HVernierTracking::mouseMoveEvent(QMouseEvent *e)
{
    Q_D(HVernierTracking);
    auto pos = d->pos;
    if (!isValid(e->localPos()) || pos == -1)
        return false;

    emit vernierPosChanged(d->verniers[pos]);
    d->verniers[pos] = e->localPos();
    emit vernierPosChanged(d->verniers[pos]);
    return true;
}
