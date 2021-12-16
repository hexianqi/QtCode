#include "HBearingCircular_p.h"
#include <QtGui/QPalette>
#include <QtGui/QPainter>

HE_BEGIN_NAMESPACE

HBearingCircular::HBearingCircular(QObject *parent) :
    HAbstractCircular(*new HBearingCircularPrivate, parent)
{
}

HBearingCircular::HBearingCircular(HBearingCircularPrivate &p, QObject *parent) :
    HAbstractCircular(p, parent)
{
}

void HBearingCircular::initialize(QVariantMap param)
{
    if (param.contains("background"))
        setBackground(param.value("background").value<QColor>());
    if (param.contains("foreground"))
        setForeground(param.value("foreground").value<QColor>());
}

QString HBearingCircular::typeName()
{
    return "HBearingCircular";
}

void HBearingCircular::draw(QPainter *painter, double factor, QVariantMap param)
{
    Q_D(HBearingCircular);
    HAbstractCircular::draw(painter, factor, param);
    auto color1 = d->foreground;
    auto color2 = d->background;
    auto color3 = param.value("palette").value<QPalette>().window().color();

    painter->rotate(factor * 360);
    painter->save();
    painter->setPen(Qt::NoPen);
    for(int i = 0; i <= 12; i++)
    {
        color1.setAlphaF(i / 12.0);
        color2.setAlphaF(i / 12.0);

        painter->setBrush(color1);
        painter->drawPie(-50, -50, 100, 100, 4 * 16, 28 * 16);
        painter->setBrush(color3);
        painter->drawPie(-40, -40,  80,  80, 4 * 16, 28 * 16);
        painter->setBrush(color2);
        painter->drawPie(-37, -37,  74,  74, 4 * 16, 28 * 16);
        painter->rotate(30);
    }
    painter->setBrush(color3);
    painter->drawEllipse(-20, -20, 40, 40);
    painter->restore();
}

QColor HBearingCircular::background() const
{
    Q_D(const HBearingCircular);
    return d->background;
}

QColor HBearingCircular::foreground() const
{
    Q_D(const HBearingCircular);
    return d->foreground;
}

void HBearingCircular::setBackground(const QColor &value)
{
    Q_D(HBearingCircular);
    if (d->background == value)
        return;
    d->background = value;
    emit dataChanged();
}

void HBearingCircular::setForeground(const QColor &value)
{
    Q_D(HBearingCircular);
    if (d->foreground == value)
        return;
    d->foreground = value;
    emit dataChanged();
}

HE_END_NAMESPACE
