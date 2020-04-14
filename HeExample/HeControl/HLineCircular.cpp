#include "HLineCircular_p.h"
#include <QtGui/QPainter>

HE_CONTROL_BEGIN_NAMESPACE

HLineCircular::HLineCircular(QObject *parent) :
    HAbstractCircular(*new HLineCircularPrivate, parent)
{
}

HLineCircular::HLineCircular(HLineCircularPrivate &p, QObject *parent) :
    HAbstractCircular(p, parent)
{
}

void HLineCircular::initialize(QVariantMap param)
{
    if (param.contains("foreground"))
        setForeground(param.value("foreground").value<QColor>());
}

QString HLineCircular::typeName()
{
    return "HLineCircular";
}

void HLineCircular::draw(QPainter *painter, double factor, QVariantMap param)
{
    Q_D(HLineCircular);
    HAbstractCircular::draw(painter, factor, param);
    auto c = d->foreground;
    painter->rotate(factor * 360);
    painter->save();
    painter->setPen(Qt::NoPen);
    for(int i = 0; i <= 10; i++)
    {
        c.setAlphaF(i / 10.0);
        painter->setBrush(c);
        painter->drawRoundedRect(20, -3, 30, 6, 2, 2);
        painter->rotate(36);
    }
    painter->restore();
}

QColor HLineCircular::foreground() const
{
    Q_D(const HLineCircular);
    return d->foreground;
}

void HLineCircular::setForeground(const QColor &value)
{
    Q_D(HLineCircular);
    if (d->foreground == value)
        return;
    d->foreground = value;
    emit dataChanged();
}

HE_CONTROL_END_NAMESPACE
