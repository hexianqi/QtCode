#include "HVernierTracking_p.h"
#include <QStyleOptionFocusRect>
#include <QStylePainter>
#include <QMouseEvent>

HVernierTrackingPrivate::HVernierTrackingPrivate(Qt::Orientation o, QWidget *p)
    : HAbstractMouseStrategyPrivate(p)
{
    orientation = o;
    validRegion.setRect(0, 0, 1, 1);
}

void HVernierTrackingPrivate::setValidRegion(QRectF value)
{
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
}

void HVernierTrackingPrivate::setVernier(int i, double percent)
{
    if (i < 0 || i >= verniers.size())
        return;

    percent = qBound(0.0, percent, 1.0);
    verniers[i].rx() = validRegion.left() + validRegion.width() * percent;
    verniers[i].ry() = validRegion.top() + validRegion.height() * percent;
}

void HVernierTrackingPrivate::resizeVernier(int size)
{
    verniers.resize(size);
    if (size < 1)
        return;

    verniers[0] = validRegion.topLeft();
    for (int i = 1; i < size; i++)
        setVernier(i, i / (size - 1));
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

bool HVernierTrackingPrivate::mousePress(QPointF point)
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

void HVernierTrackingPrivate::mouseRelease()
{
    pos = -1;
    parent->unsetCursor();
}

HVernierTracking::HVernierTracking(Qt::Orientation orientation, QWidget *parent)
    : HAbstractMouseStrategy(*new HVernierTrackingPrivate(orientation, parent), parent)
{
}

HVernierTracking::HVernierTracking(HVernierTrackingPrivate &p, QWidget *parent)
    : HAbstractMouseStrategy(p, parent)
{
}

HVernierTracking::~HVernierTracking()
{
}

void HVernierTracking::setOrientation(Qt::Orientation value)
{
    Q_D(HVernierTracking);
    if (d->orientation == value)
        return;
    d->orientation = value;
    emit orientationChanged(value);
}

void HVernierTracking::setValidRegion(QRectF value)
{
    Q_D(HVernierTracking);
    d->setValidRegion(value);
}

void HVernierTracking::setVernierColor(QColor value)
{
    Q_D(HVernierTracking);
    d->color = value;
}

void HVernierTracking::setVernier(int i, double percent)
{
    Q_D(HVernierTracking);
    d->setVernier(i, percent);
    emit vernierChanged(d->verniers[i]);
}

void HVernierTracking::resizeVernier(int size)
{
    Q_D(HVernierTracking);
    d->resizeVernier(size);
    emit vernierSizeChanged(size);
}

Qt::Orientation HVernierTracking::orientation()
{
    Q_D(HVernierTracking);
    return d->orientation;
}

QVector<QPointF> HVernierTracking::verniers()
{
    Q_D(HVernierTracking);
    return d->verniers;
}

void HVernierTracking::paintEvent(QPaintEvent *)
{
    Q_D(HVernierTracking);
    if (!isEnable())
        return;
    d->paintVernier();
}

bool HVernierTracking::mousePressEvent(QMouseEvent *e)
{
    Q_D(HVernierTracking);
    if (!isEnable() || e->button() != Qt::LeftButton)
        return false;
    return d->mousePress(e->localPos());
}

bool HVernierTracking::mouseMoveEvent(QMouseEvent *e)
{
    Q_D(HVernierTracking);
    auto pos = d->pos;
    if (!d->isValid(e->localPos()) || pos == -1)
        return false;

    emit vernierChanged(d->verniers[pos]);
    d->verniers[pos] = e->localPos();
    emit vernierChanged(d->verniers[pos]);
    return true;
}

bool HVernierTracking::mouseReleaseEvent(QMouseEvent *e)
{
    Q_D(HVernierTracking);
    if (!isEnable() || e->button() != Qt::LeftButton || d->pos == -1 )
        return false;

    emit vernierChanged(d->verniers[d->pos]);
    d->mouseRelease();
    return true;
}
