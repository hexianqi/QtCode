#include "HLineWait_p.h"
#include <QtGui/QPainter>

HE_CONTROL_BEGIN_NAMESPACE

HLineWait::HLineWait(QObject *parent) :
    HAbstractWait(*new HLineWaitPrivate, parent)
{
}

HLineWait::HLineWait(HLineWaitPrivate &p, QObject *parent) :
    HAbstractWait(p, parent)
{
}

HLineWait::~HLineWait()
{
}

void HLineWait::initialize(QVariantMap param)
{
    if (param.contains("foreground"))
        setForeground(param.value("foreground").value<QColor>());
}

QString HLineWait::typeName()
{
    return "HLineWait";
}

void HLineWait::draw(QPainter *painter, QVariantMap param)
{
    Q_D(HLineWait);
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
        painter->drawRoundedRect(20, -3, 30, 6, 2, 2);
        painter->rotate(36);
    }
    painter->restore();
}

QColor HLineWait::foreground() const
{
    Q_D(const HLineWait);
    return d->foreground;
}

void HLineWait::setForeground(const QColor &value)
{
    Q_D(HLineWait);
    if (d->foreground == value)
        return;
    d->foreground = value;
    emit dataChanged();
}

HE_CONTROL_END_NAMESPACE
