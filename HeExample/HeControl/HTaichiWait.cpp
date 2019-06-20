#include "HTaichiWait_p.h"
#include <QtGui/QPainter>

HE_CONTROL_BEGIN_NAMESPACE

HTaichiWait::HTaichiWait(QObject *parent) :
    HAbstractWait(*new HTaichiWaitPrivate, parent)
{
}

HTaichiWait::HTaichiWait(HTaichiWaitPrivate &p, QObject *parent) :
    HAbstractWait(p, parent)
{
}

HTaichiWait::~HTaichiWait()
{
}

void HTaichiWait::initialize(QVariantMap param)
{
    if (param.contains("background"))
        setBackground(param.value("background").value<QColor>());
    if (param.contains("foreground"))
        setForeground(param.value("foreground").value<QColor>());
}

QString HTaichiWait::typeName()
{
    return "HTaichiWait";
}

void HTaichiWait::draw(QPainter *painter, QVariantMap param)
{
    Q_D(HTaichiWait);
    HAbstractWait::draw(painter, param);
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

QColor HTaichiWait::background() const
{
    Q_D(const HTaichiWait);
    return d->background;
}

QColor HTaichiWait::foreground() const
{
    Q_D(const HTaichiWait);
    return d->foreground;
}

void HTaichiWait::setBackground(const QColor &value)
{
    Q_D(HTaichiWait);
    if (d->background == value)
        return;
    d->background = value;
    emit dataChanged();
}

void HTaichiWait::setForeground(const QColor &value)
{
    Q_D(HTaichiWait);
    if (d->foreground == value)
        return;
    d->foreground = value;
    emit dataChanged();
}

HE_CONTROL_END_NAMESPACE
