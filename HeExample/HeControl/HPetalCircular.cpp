#include "HPetalCircular_p.h"
#include <QtGui/QPainter>

HE_CONTROL_BEGIN_NAMESPACE

HPetalCircular::HPetalCircular(QObject *parent) :
    HAbstractCircular(*new HPetalCircularPrivate, parent)
{
}

HPetalCircular::HPetalCircular(HPetalCircularPrivate &p, QObject *parent) :
    HAbstractCircular(p, parent)
{
}

void HPetalCircular::initialize(QVariantMap param)
{
    if (param.contains("foreground"))
        setForeground(param.value("foreground").value<QColor>());
}

QString HPetalCircular::typeName()
{
    return "HPetalCircular";
}

void HPetalCircular::draw(QPainter *painter, double factor, QVariantMap param)
{
    Q_D(HPetalCircular);
    HAbstractCircular::draw(painter, factor, param);
    auto c = d->foreground;
    painter->rotate(factor * 360);
    painter->save();
    painter->setPen(Qt::NoPen);
    for(int i = 0; i <= 10; i++)
    {
        c.setAlphaF(i / 10.0);
        painter->setBrush(c);
        painter->drawEllipse(20, -6, 30, 12);
        painter->rotate(36);
    }
    painter->restore();
}

QColor HPetalCircular::foreground() const
{
    Q_D(const HPetalCircular);
    return d->foreground;
}

void HPetalCircular::setForeground(const QColor &value)
{
    Q_D(HPetalCircular);
    if (d->foreground == value)
        return;
    d->foreground = value;
    emit dataChanged();
}

HE_CONTROL_END_NAMESPACE
