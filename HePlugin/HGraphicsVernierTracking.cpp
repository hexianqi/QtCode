#include "HGraphicsVernierTracking_p.h"
#include <QMouseEvent>
#include <QGraphicsLineItem>
#include <QPen>

HGraphicsVernierTrackingPrivate::HGraphicsVernierTrackingPrivate(Qt::Orientation o, QGraphicsItem *gp, QWidget *p)
    : HAbstractVernierTrackingPrivate(o, p)
{
    gparent = gp;
}

bool HGraphicsVernierTrackingPrivate::setOrientation(Qt::Orientation value)
{
    if (!HAbstractVernierTrackingPrivate::setOrientation(value))
        return false;
    setLines();
    return true;
}

bool HGraphicsVernierTrackingPrivate::setValidRegion(QRectF value)
{
    if (!HAbstractVernierTrackingPrivate::setValidRegion(value))
        return false;
    setLines();
    return true;
}

bool HGraphicsVernierTrackingPrivate::setVernierColor(QColor value)
{
    if (!HAbstractVernierTrackingPrivate::setVernierColor(value))
        return false;
    setLinesColor(value);
    return true;
}

bool HGraphicsVernierTrackingPrivate::setVernier(int i, double percent)
{
    if (!HAbstractVernierTrackingPrivate::setVernier(i, percent))
        return false;
    setLine(i);
    return true;
}

void HGraphicsVernierTrackingPrivate::resizeVernier(int size)
{
    lines.clear();
    for (int i = 0; i < size; i++)
    {
        auto item = new QGraphicsLineItem(gparent);
        item->setPen(QPen(color));
        item->setZValue(99);
        lines << item;
    }
    HAbstractVernierTrackingPrivate::resizeVernier(size);
}

void HGraphicsVernierTrackingPrivate::setLinesVisible(bool b)
{
    for (auto l : lines)
        l->setVisible(b);
}

void HGraphicsVernierTrackingPrivate::setLinesColor(QColor color)
{
    for (auto l : lines)
        l->setPen(QPen(color));
}

void HGraphicsVernierTrackingPrivate::setLine(int pos)
{
    if (orientation == Qt::Horizontal)
        lines[pos]->setLine(validRegion.left() + 2, verniers[pos].y(), validRegion.right() - 2, verniers[pos].y());
    else
        lines[pos]->setLine(verniers[pos].x(), validRegion.top() + 2, verniers[pos].x(), validRegion.bottom() - 2);
}

void HGraphicsVernierTrackingPrivate::setLines()
{
    for (int i = 0; i < lines.size(); i++)
        setLine(i);
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
    Q_D(HGraphicsVernierTracking);
    if (!HAbstractVernierTracking::setEnable(b))
        return false;
    d->setLinesVisible(b);
    return true;
}

bool HGraphicsVernierTracking::mouseMoveEvent(QMouseEvent *e)
{
    Q_D(HGraphicsVernierTracking);
    auto pos = d->pos;
    if (!d->isValid(e->localPos()) || pos == -1)
        return false;

    d->verniers[pos] = e->localPos();
    d->setLine(pos);
    emit vernierPosChanged(d->verniers[pos]);
    return true;
}
