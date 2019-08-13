#include "HCircleCircular_p.h"
#include <QtGui/QPainter>

HE_CONTROL_BEGIN_NAMESPACE

HCircleCircular::HCircleCircular(QObject *parent) :
    HAbstractCircular(*new HCircleCircularPrivate, parent)
{
}

HCircleCircular::HCircleCircular(HCircleCircularPrivate &p, QObject *parent) :
    HAbstractCircular(p, parent)
{
}

HCircleCircular::~HCircleCircular()
{
}

void HCircleCircular::initialize(QVariantMap param)
{
    if (param.contains("foreground"))
        setForeground(param.value("foreground").value<QColor>());
}

QString HCircleCircular::typeName()
{
    return "HCircleCircular";
}

void HCircleCircular::draw(QPainter *painter, double factor, QVariantMap param)
{
    Q_D(HCircleCircular);
    HAbstractCircular::draw(painter, factor, param);
    auto c = d->foreground;
    painter->rotate(factor * 360);
    painter->save();
    painter->setPen(Qt::NoPen);
    for(int i = 0; i <= 10; i++)
    {
        c.setAlphaF(i / 10.0);
        painter->setBrush(c);
        painter->drawEllipse(30, -10, 20, 20);
        painter->rotate(36);
    }
    painter->restore();
}

QColor HCircleCircular::foreground() const
{
    Q_D(const HCircleCircular);
    return d->foreground;
}

void HCircleCircular::setForeground(const QColor &value)
{
    Q_D(HCircleCircular);
    if (d->foreground == value)
        return;
    d->foreground = value;
    emit dataChanged();
}

HE_CONTROL_END_NAMESPACE
