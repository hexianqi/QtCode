#include "HTaichiCircular_p.h"
#include <QtGui/QPainter>

HE_CONTROL_BEGIN_NAMESPACE

HTaichiCircular::HTaichiCircular(QObject *parent) :
    HAbstractCircular(*new HTaichiCircularPrivate, parent)
{
}

HTaichiCircular::HTaichiCircular(HTaichiCircularPrivate &p, QObject *parent) :
    HAbstractCircular(p, parent)
{
}

HTaichiCircular::~HTaichiCircular()
{
}

void HTaichiCircular::initialize(QVariantMap param)
{
    if (param.contains("background"))
        setBackground(param.value("background").value<QColor>());
    if (param.contains("foreground"))
        setForeground(param.value("foreground").value<QColor>());
}

QString HTaichiCircular::typeName()
{
    return "HTaichiCircular";
}

void HTaichiCircular::draw(QPainter *painter, QVariantMap param)
{
    Q_D(HTaichiCircular);
    HAbstractCircular::draw(painter, param);
    auto reverse = param.value("reverse", false).toBool();
    auto value = param.value("value", 0).toInt();
    auto rect = QRectF(-50, -50, 100, 100);
    auto rectb1 = QRectF(-25, 0, 50, 50);
    auto rectb2 = QRectF(-50 / 8, -50 * 5 / 8, 50 / 4, 50 / 4);
    auto rectf1 = QRectF(-25, -50, 50, 50);
    auto rectf2 = QRectF(-50 / 8, 50 * 3 / 8, 50 / 4, 50 / 4);
    if (reverse)
    {
        qSwap(rectb1, rectf1);
        qSwap(rectb2, rectf2);
    }

    painter->rotate(value);
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(d->foreground);
    painter->drawPie(rect, 90 * 16, 180 * 16);
    painter->setBrush(d->background);
    painter->drawPie(rect, 270 * 16, 180 * 16);
    painter->drawEllipse(rectb1);
    painter->setBrush(d->foreground);
    painter->drawEllipse(rectf1);
    painter->drawEllipse(rectf2);
    painter->setBrush(d->background);
    painter->drawEllipse(rectb2);
    painter->restore();
}

QColor HTaichiCircular::background() const
{
    Q_D(const HTaichiCircular);
    return d->background;
}

QColor HTaichiCircular::foreground() const
{
    Q_D(const HTaichiCircular);
    return d->foreground;
}

void HTaichiCircular::setBackground(const QColor &value)
{
    Q_D(HTaichiCircular);
    if (d->background == value)
        return;
    d->background = value;
    emit dataChanged();
}

void HTaichiCircular::setForeground(const QColor &value)
{
    Q_D(HTaichiCircular);
    if (d->foreground == value)
        return;
    d->foreground = value;
    emit dataChanged();
}

HE_CONTROL_END_NAMESPACE
