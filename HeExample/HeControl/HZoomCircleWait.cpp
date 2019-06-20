#include "HZoomCircleWait_p.h"
#include <QtGui/QPainter>

HE_CONTROL_BEGIN_NAMESPACE

HZoomCircleWait::HZoomCircleWait(QObject *parent) :
    HAbstractWait(*new HZoomCircleWaitPrivate, parent)
{
}

HZoomCircleWait::HZoomCircleWait(HZoomCircleWaitPrivate &p, QObject *parent) :
    HAbstractWait(p, parent)
{
}

HZoomCircleWait::~HZoomCircleWait()
{
}

void HZoomCircleWait::initialize(QVariantMap param)
{
    if (param.contains("foreground"))
        setForeground(param.value("foreground").value<QColor>());
}

QString HZoomCircleWait::typeName()
{
    return "HZoomCircleWait";
}

void HZoomCircleWait::draw(QPainter *painter, QVariantMap param)
{
    Q_D(HZoomCircleWait);
    HAbstractWait::draw(painter, param);
    auto value = param.value("value", 0).toInt();
    auto radious = calcRaidous(value);

    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(d->foreground);
    painter->drawEllipse(-radious, -radious, 2 * radious, 2 * radious);
    painter->restore();
}

QColor HZoomCircleWait::foreground() const
{
    Q_D(const HZoomCircleWait);
    return d->foreground;
}

double HZoomCircleWait::minimum() const
{
    Q_D(const HZoomCircleWait);
    return d->minimum;
}

bool HZoomCircleWait::bounce() const
{
    Q_D(const HZoomCircleWait);
    return d->bounce;
}

void HZoomCircleWait::setForeground(const QColor &value)
{
    Q_D(HZoomCircleWait);
    if (d->foreground == value)
        return;
    d->foreground = value;
    emit dataChanged();
}

void HZoomCircleWait::setMinimum(int value)
{
    Q_D(HZoomCircleWait);
    value = qBound(0, value, 50);
    if (d->minimum == value)
        return;
    d->minimum = value;
    emit dataChanged();
}

void HZoomCircleWait::setBounce(bool b)
{
    Q_D(HZoomCircleWait);
    if (d->bounce == b)
        return;
    d->bounce = b;
    emit dataChanged();
}

double HZoomCircleWait::calcRaidous(int value)
{
    Q_D(HZoomCircleWait);
    auto span = (50 - d->minimum) / 360.0;
    if (d->bounce)
    {
        value = qAbs(qAbs(value) - 180);
        return d->minimum + 2 * span * value;
    }
    return value >= 0 ? d->minimum + span * value : 50 + span * value;
}

HE_CONTROL_END_NAMESPACE
