#include "HWheelCircular_p.h"
#include <QtGui/QPainter>

HE_BEGIN_NAMESPACE

HWheelCircular::HWheelCircular(QObject *parent) :
    HAbstractCircular(*new HWheelCircularPrivate, parent)
{
}

HWheelCircular::HWheelCircular(HWheelCircularPrivate &p, QObject *parent) :
    HAbstractCircular(p, parent)
{
}

void HWheelCircular::initialize(QVariantMap param)
{
    if (param.contains("backgroundStart"))
        setBackgroundStart(param.value("backgroundStart").value<QColor>());
    if (param.contains("backgroundEnd"))
        setBackgroundEnd(param.value("backgroundEnd").value<QColor>());
    if (param.contains("foreground1Start"))
        setForeground1Start(param.value("foreground1Start").value<QColor>());
    if (param.contains("foreground1End"))
        setForeground1End(param.value("foreground1End").value<QColor>());
    if (param.contains("foreground2Start"))
        setForeground2Start(param.value("foreground2Start").value<QColor>());
    if (param.contains("foreground2End"))
        setForeground2End(param.value("foreground2End").value<QColor>());
}

QString HWheelCircular::typeName()
{
    return "HWheelCircular";
}

void HWheelCircular::draw(QPainter *painter, double factor, QVariantMap param)
{
    HAbstractCircular::draw(painter, factor, param);
    painter->rotate(factor * 360);
    drawBackground(painter);
    drawCircle(painter);
}

QColor HWheelCircular::backgroundStart() const
{
    Q_D(const HWheelCircular);
    return d->backgroundStart;
}

QColor HWheelCircular::backgroundEnd() const
{
    Q_D(const HWheelCircular);
    return d->backgroundEnd;
}

QColor HWheelCircular::foreground1Start() const
{
    Q_D(const HWheelCircular);
    return d->foreground1Start;
}

QColor HWheelCircular::foreground1End() const
{
    Q_D(const HWheelCircular);
    return d->foreground1End;
}

QColor HWheelCircular::foreground2Start() const
{
    Q_D(const HWheelCircular);
    return d->foreground2Start;
}

QColor HWheelCircular::foreground2End() const
{
    Q_D(const HWheelCircular);
    return d->foreground2End;
}

void HWheelCircular::setBackgroundStart(const QColor &value)
{
    Q_D(HWheelCircular);
    if (d->backgroundStart == value)
        return;
    d->backgroundStart = value;
    emit dataChanged();
}

void HWheelCircular::setBackgroundEnd(const QColor &value)
{
    Q_D(HWheelCircular);
    if (d->backgroundEnd == value)
        return;
    d->backgroundEnd = value;
    emit dataChanged();
}

void HWheelCircular::setForeground1Start(const QColor &value)
{
    Q_D(HWheelCircular);
    if (d->foreground1Start == value)
        return;
    d->foreground1Start = value;
    emit dataChanged();
}

void HWheelCircular::setForeground1End(const QColor &value)
{
    Q_D(HWheelCircular);
    if (d->foreground1End == value)
        return;
    d->foreground1End = value;
    emit dataChanged();
}

void HWheelCircular::setForeground2Start(const QColor &value)
{
    Q_D(HWheelCircular);
    if (d->foreground2Start == value)
        return;
    d->foreground2Start = value;
    emit dataChanged();
}

void HWheelCircular::setForeground2End(const QColor &value)
{
    Q_D(HWheelCircular);
    if (d->foreground2End == value)
        return;
    d->foreground2End = value;
    emit dataChanged();
}

void HWheelCircular::drawBackground(QPainter *painter)
{
    auto gradient = QRadialGradient(0, 0, 50, 0, 0);
    gradient.setColorAt(0.0, backgroundStart());
    gradient.setColorAt(1.0, backgroundEnd());
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(gradient);
    painter->drawEllipse(-50, -50, 100, 100);
    painter->restore();
}

void HWheelCircular::drawCircle(QPainter *painter)
{
    auto rect = QRectF(-40, -40, 80, 80);
    auto gradient1 = QRadialGradient(0, 0, 40, 0, 0);
    gradient1.setColorAt(0.0, foreground1Start());
    gradient1.setColorAt(1.0, foreground1End());
    auto gradient2 = QRadialGradient(0, 0, 40, 0, 0);
    gradient2.setColorAt(0.0, foreground2Start());
    gradient2.setColorAt(1.0, foreground2End());
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(gradient1);
    painter->drawPie(rect, 90 * 16, 90 * 16);
    painter->drawPie(rect, 270 * 16, 90 * 16);
    painter->setBrush(gradient2);
    painter->drawPie(rect, 0, 90 * 16);
    painter->drawPie(rect, 180 * 16, 90 * 16);
    painter->restore();
}

HE_END_NAMESPACE
