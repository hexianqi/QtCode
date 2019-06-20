#include "HCircleWait_p.h"
#include <QtGui/QPainter>

HE_CONTROL_BEGIN_NAMESPACE

HCircleWait::HCircleWait(QObject *parent) :
    HAbstractWait(*new HCircleWaitPrivate, parent)
{
}

HCircleWait::HCircleWait(HCircleWaitPrivate &p, QObject *parent) :
    HAbstractWait(p, parent)
{
}

HCircleWait::~HCircleWait()
{
}

void HCircleWait::initialize(QVariantMap param)
{
    if (param.contains("foreground"))
        setForeground(param.value("foreground").value<QColor>());
}

QString HCircleWait::typeName()
{
    return "HCircleWait";
}

void HCircleWait::draw(QPainter *painter, QVariantMap param)
{
    Q_D(HCircleWait);
    HAbstractWait::draw(painter, param);
    auto value = param.value("value", 0).toInt();
    auto c = d->foreground;

    painter->rotate(value);
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

QColor HCircleWait::foreground() const
{
    Q_D(const HCircleWait);
    return d->foreground;
}

void HCircleWait::setForeground(const QColor &value)
{
    Q_D(HCircleWait);
    if (d->foreground == value)
        return;
    d->foreground = value;
    emit dataChanged();
}

HE_CONTROL_END_NAMESPACE
