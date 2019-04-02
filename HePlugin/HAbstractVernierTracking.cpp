#include "HAbstractVernierTracking_p.h"
#include <QMouseEvent>
#include <QWidget>

HAbstractVernierTrackingPrivate::HAbstractVernierTrackingPrivate(Qt::Orientation o, QWidget *p)
    : HAbstractMouseStrategyPrivate(p)
{
    orientation = o;
    validRegion.setRect(0, 0, 1, 1);
}

HAbstractVernierTracking::HAbstractVernierTracking(Qt::Orientation orientation, QWidget *parent)
    : HAbstractMouseStrategy(*new HAbstractVernierTrackingPrivate(orientation, parent), parent)
{
}

HAbstractVernierTracking::HAbstractVernierTracking(HAbstractVernierTrackingPrivate &p, QWidget *parent)
    : HAbstractMouseStrategy(p, parent)
{
}

HAbstractVernierTracking::~HAbstractVernierTracking()
{
}

bool HAbstractVernierTracking::setValidRegion(QRectF value)
{
    Q_D(HAbstractVernierTracking);
    if (d->validRegion == value)
        return false;

    auto dx = value.width() / d->validRegion.width();
    auto dy = value.height() / d->validRegion.height();
    for (int i = 0; i < d->verniers.count(); i++)
    {
        auto x = value.left() + (d->verniers[i].x() - d->validRegion.left()) * dx;
        auto y = value.top() + (d->verniers[i].y() - d->validRegion.top()) * dy;
        x = qBound(value.left(), x, value.right());
        y = qBound(value.top(), y, value.bottom());
        d->verniers[i] = QPointF(x, y);
    }
    d->validRegion = value;
    return true;
}

bool HAbstractVernierTracking::setOrientation(Qt::Orientation value)
{
    Q_D(HAbstractVernierTracking);
    if (d->orientation == value)
        return false;
    d->orientation = value;
    emit orientationChanged(value);
    return true;
}

bool HAbstractVernierTracking::setVernierColor(QColor value)
{
    Q_D(HAbstractVernierTracking);
    if (d->color == value)
        return false;
    d->color = value;
    return true;
}

bool HAbstractVernierTracking::setVernier(int i, double percent)
{
    Q_D(HAbstractVernierTracking);
    if (i < 0 || i >= d->verniers.size())
        return false;

    percent = qBound(0.0, percent, 1.0);
    d->verniers[i].rx() = d->validRegion.left() + d->validRegion.width() * percent;
    d->verniers[i].ry() = d->validRegion.top() + d->validRegion.height() * percent;
    emit vernierPosChanged(d->verniers[i]);
    return true;
}

void HAbstractVernierTracking::resizeVernier(int size)
{
    Q_D(HAbstractVernierTracking);
    d->verniers.resize(size);
    if (size > 0)
    {
        d->verniers[0] = d->validRegion.topLeft();
        for (int i = 1; i < size; i++)
            setVernier(i, i / (size - 1));
    }
    emit vernierSizeChanged(size);
}

Qt::Orientation HAbstractVernierTracking::orientation()
{
    Q_D(HAbstractVernierTracking);
    return d->orientation;
}

QVector<QPointF> HAbstractVernierTracking::verniers()
{
    Q_D(HAbstractVernierTracking);
    return d->verniers;
}

bool HAbstractVernierTracking::mousePressEvent(QMouseEvent *e)
{
    Q_D(HAbstractVernierTracking);
    if (!isEnable() || e->button() != Qt::LeftButton || !isValid(e->localPos()))
        return false;
    for (int i = 0; i < d->verniers.size(); i++)
    {
        if (d->orientation == Qt::Horizontal && qAbs(e->localPos().y() - d->verniers[i].y()) < 5)
        {
            d->pos = i;
            d->parent->setCursor(Qt::SizeVerCursor);
            return true;
        }
        if (d->orientation == Qt::Vertical && qAbs(e->localPos().x() - d->verniers[i].x()) < 5)
        {
            d->pos = i;
            d->parent->setCursor(Qt::SizeHorCursor);
            return true;
        }
    }
    return false;
}

bool HAbstractVernierTracking::mouseReleaseEvent(QMouseEvent *e)
{
    Q_D(HAbstractVernierTracking);
    if (!isEnable() || e->button() != Qt::LeftButton || d->pos == -1 )
        return false;

    emit vernierPosChanged(d->verniers[d->pos]);
    d->pos = -1;
    d->parent->unsetCursor();
    return true;
}
