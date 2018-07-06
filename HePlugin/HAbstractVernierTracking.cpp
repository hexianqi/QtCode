#include "HAbstractVernierTracking_p.h"
#include <QMouseEvent>
#include <QWidget>

HAbstractVernierTrackingPrivate::HAbstractVernierTrackingPrivate(Qt::Orientation o, QWidget *p)
    : HAbstractMouseStrategyPrivate(p)
{
    orientation = o;
    validRegion.setRect(0, 0, 1, 1);
}

bool HAbstractVernierTrackingPrivate::setOrientation(Qt::Orientation value)
{
    if (orientation == value)
        return false;

    orientation = value;
    return true;
}

bool HAbstractVernierTrackingPrivate::setValidRegion(QRectF value)
{
    if (validRegion == value)
        return false;

    auto dx = value.width() / validRegion.width();
    auto dy = value.height() / validRegion.height();
    for (int i = 0; i < verniers.count(); i++)
    {
        auto x = value.left() + (verniers[i].x() - validRegion.left()) * dx;
        auto y = value.top() + (verniers[i].y() - validRegion.top()) * dy;
        x = qBound(value.left(), x, value.right());
        y = qBound(value.top(), y, value.bottom());
        verniers[i] = QPointF(x, y);
    }
    validRegion = value;
    return true;
}

bool HAbstractVernierTrackingPrivate::setVernierColor(QColor value)
{
    if (color == value)
        return false;

    color = value;
    return true;
}

bool HAbstractVernierTrackingPrivate::setVernier(int i, double percent)
{
    if (i < 0 || i >= verniers.size())
        return false;

    percent = qBound(0.0, percent, 1.0);
    verniers[i].rx() = validRegion.left() + validRegion.width() * percent;
    verniers[i].ry() = validRegion.top() + validRegion.height() * percent;
    return true;
}

void HAbstractVernierTrackingPrivate::resizeVernier(int size)
{
    verniers.resize(size);
    if (size < 1)
        return;

    verniers[0] = validRegion.topLeft();
    for (int i = 1; i < size; i++)
        setVernier(i, i / (size - 1));
}

bool HAbstractVernierTrackingPrivate::mousePress(QPointF point)
{
    for (int i = 0; i < verniers.size(); i++)
    {
        if (orientation == Qt::Horizontal && qAbs(point.y() - verniers[i].y()) < 5)
        {
            pos = i;
            parent->setCursor(Qt::SizeVerCursor);
            return true;
        }
        if (orientation == Qt::Vertical && qAbs(point.x() - verniers[i].x()) < 5)
        {
            pos = i;
            parent->setCursor(Qt::SizeHorCursor);
            return true;
        }
    }
    return false;
}

void HAbstractVernierTrackingPrivate::mouseRelease()
{
    pos = -1;
    parent->unsetCursor();
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
    return d->setValidRegion(value);
}

void HAbstractVernierTracking::setOrientation(Qt::Orientation value)
{
    Q_D(HAbstractVernierTracking);
    if (d->setOrientation(value))
        emit orientationChanged(value);
}

void HAbstractVernierTracking::setVernierColor(QColor value)
{
    Q_D(HAbstractVernierTracking);
    d->setVernierColor(value);
}

void HAbstractVernierTracking::setVernier(int i, double percent)
{
    Q_D(HAbstractVernierTracking);
    if (d->setVernier(i, percent))
        emit vernierPosChanged(d->verniers[i]);
}

void HAbstractVernierTracking::resizeVernier(int size)
{
    Q_D(HAbstractVernierTracking);
    d->resizeVernier(size);
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
    if (!isEnable() || e->button() != Qt::LeftButton)
        return false;
    return d->mousePress(e->localPos());
}

bool HAbstractVernierTracking::mouseReleaseEvent(QMouseEvent *e)
{
    Q_D(HAbstractVernierTracking);
    if (!isEnable() || e->button() != Qt::LeftButton || d->pos == -1 )
        return false;

    emit vernierPosChanged(d->verniers[d->pos]);
    d->mouseRelease();
    return true;
}
