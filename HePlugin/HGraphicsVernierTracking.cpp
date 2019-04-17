#include "HGraphicsVernierTracking_p.h"
#include <QtGui/QMouseEvent>
#include <QtGui/QPen>
#include <QtWidgets/QGraphicsLineItem>

HGraphicsVernierTrackingPrivate::HGraphicsVernierTrackingPrivate(Qt::Orientation o, QGraphicsItem *gp, QWidget *p)
    : HAbstractVernierTrackingPrivate(o, p)
{
    gparent = gp;
}

HGraphicsVernierTracking::HGraphicsVernierTracking(Qt::Orientation orientation, QGraphicsItem *gpatent, QWidget *parent)
    : HAbstractVernierTracking(*new HGraphicsVernierTrackingPrivate(orientation, gpatent, parent), parent)
{
}

HGraphicsVernierTracking::HGraphicsVernierTracking(HGraphicsVernierTrackingPrivate &p, QWidget *parent)
    : HAbstractVernierTracking(p, parent)
{
}

HGraphicsVernierTracking::~HGraphicsVernierTracking()
{
}

bool HGraphicsVernierTracking::setEnable(bool b)
{
    if (!HAbstractVernierTracking::setEnable(b))
        return false;
    setLinesVisible(b);
    return true;
}

bool HGraphicsVernierTracking::setValidRegion(QRectF value)
{
    if (!HAbstractVernierTracking::setValidRegion(value))
        return false;
    setLines();
    return true;
}

bool HGraphicsVernierTracking::setOrientation(Qt::Orientation value)
{
    if (!HAbstractVernierTracking::setOrientation(value))
        return false;
    setLines();
    return true;
}

bool HGraphicsVernierTracking::setVernierColor(QColor value)
{
    if (!HAbstractVernierTracking::setVernierColor(value))
        return false;
    setLinesColor(value);
    return true;

}

bool HGraphicsVernierTracking::setVernier(int i, double percent)
{
    if (!HAbstractVernierTracking::setVernier(i, percent))
        return false;
    setLine(i);
    return true;
}

void HGraphicsVernierTracking::resizeVernier(int size)
{
    Q_D(HGraphicsVernierTracking);
    d->lines.clear();
    for (int i = 0; i < size; i++)
    {
        auto item = new QGraphicsLineItem(d->gparent);
        item->setPen(QPen(d->color));
        item->setZValue(99);
        d->lines << item;
    }
    HAbstractVernierTracking::resizeVernier(size);
}

bool HGraphicsVernierTracking::mouseMoveEvent(QMouseEvent *e)
{
    Q_D(HGraphicsVernierTracking);
    auto pos = d->pos;
    if (!isValid(e->localPos()) || pos == -1)
        return false;

    d->verniers[pos] = e->localPos();
    setLine(pos);
    emit vernierPosChanged(d->verniers[pos]);
    return true;
}

void HGraphicsVernierTracking::setLinesVisible(bool b)
{
    Q_D(HGraphicsVernierTracking);
    for (auto l : d->lines)
        l->setVisible(b);
}

void HGraphicsVernierTracking::setLinesColor(QColor color)
{
    Q_D(HGraphicsVernierTracking);
    for (auto l : d->lines)
        l->setPen(QPen(color));
}

void HGraphicsVernierTracking::setLine(int pos)
{
    Q_D(HGraphicsVernierTracking);
    if (d->orientation == Qt::Horizontal)
        d->lines[pos]->setLine(d->validRegion.left() + 2, d->verniers[pos].y(), d->validRegion.right() - 2, d->verniers[pos].y());
    else
        d->lines[pos]->setLine(d->verniers[pos].x(), d->validRegion.top() + 2, d->verniers[pos].x(), d->validRegion.bottom() - 2);
}

void HGraphicsVernierTracking::setLines()
{
    Q_D(HGraphicsVernierTracking);
    for (int i = 0; i < d->lines.size(); i++)
        setLine(i);
}
