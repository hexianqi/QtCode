#include "HBubbleCircular_p.h"
#include <QtGui/QPainter>

HE_BEGIN_NAMESPACE

HBubbleCircular::HBubbleCircular(QObject *parent) :
    HAbstractCircular(*new HBubbleCircularPrivate, parent)
{
}

HBubbleCircular::HBubbleCircular(HBubbleCircularPrivate &p, QObject *parent) :
    HAbstractCircular(p, parent)
{
}

void HBubbleCircular::initialize(QVariantMap param)
{
    if (param.contains("foreground"))
        setForeground(param.value("foreground").value<QColor>());
}

QString HBubbleCircular::typeName()
{
    return "HBubbleCircular";
}

void HBubbleCircular::draw(QPainter *painter, double factor, QVariantMap param)
{
    Q_D(HBubbleCircular);
    HAbstractCircular::draw(painter, factor, param);
    auto c = d->foreground;
    painter->rotate(factor * 360);
    painter->save();
    painter->setPen(Qt::NoPen);
    for(int i = 0; i <= 10; i++)
    {
        c.setAlphaF(i / 10.0);
        painter->setBrush(c);
        painter->drawEllipse(50 - 2 * i, -i, 2 * i, 2 * i);
        painter->rotate(36);
    }
    painter->restore();
}

QColor HBubbleCircular::foreground() const
{
    Q_D(const HBubbleCircular);
    return d->foreground;
}

void HBubbleCircular::setForeground(const QColor &value)
{
    Q_D(HBubbleCircular);
    if (d->foreground == value)
        return;
    d->foreground = value;
    emit dataChanged();
}

HE_END_NAMESPACE
