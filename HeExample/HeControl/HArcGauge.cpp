#include "HArcGauge_p.h"
#include <QtGui/QPainter>

HE_CONTROL_BEGIN_NAMESPACE

HArcGaugePrivate::HArcGaugePrivate()
{
    scaleMajor = 10;
    scaleMinor = 10;
    angleStart = 45;
    angleEnd = 45;
    textColor = QColor(100, 184, 255);
    pointerColor = QColor(255, 107, 107);
    scaleColor = QColor(60, 60, 60);
    scaleLabelColor = QColor(20, 20, 20);
}

HArcGauge::HArcGauge(QWidget *parent) :
    HCircleGauge(*new HArcGaugePrivate, parent)
{
}

HArcGauge::HArcGauge(HArcGaugePrivate &p, QWidget *parent) :
    HCircleGauge(p, parent)
{
}

QColor HArcGauge::arcColor() const
{
    Q_D(const HArcGauge);
    return d->arcColor;
}

HControlType::PointerStyle HArcGauge::pointerStyle() const
{
    Q_D(const HArcGauge);
    return d->pointerStyle;
}

void HArcGauge::setArcColor(const QColor &value)
{
    Q_D(HArcGauge);
    if (d->arcColor == value)
        return;
    d->arcColor = value;
    update();
}

void HArcGauge::setPointerStyle(HControlType::PointerStyle value)
{
    Q_D(HArcGauge);
    if (d->pointerStyle == value)
        return;
    d->pointerStyle = value;
    update();
}

void HArcGauge::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    preDraw(&painter);
    // 绘制进度条
    drawProgress(&painter, 100);
    // 绘制刻度线
    drawScale(&painter, 97);
    // 绘制刻度值
    drawScaleLabel(&painter, 75);
    // 绘制指示器
    drawPointer(&painter, 100);
    // 绘制当前值
    drawValue(&painter, 100);
}

void HArcGauge::drawProgress(QPainter *painter, int /*radius*/)
{
    Q_D(HArcGauge);
    auto radius1 = 98;
    auto radius2 = 90;
    auto rect1 = QRectF(-radius1, -radius1, radius1 * 2, radius1 * 2);
    auto rect2 = QRectF(-radius2, -radius2, radius2 * 2, radius2 * 2);
    auto span = 360 - d->angleStart - d->angleEnd;
    auto start = 270 - d->angleStart - span;
    painter->save();
    painter->setPen(QPen(d->arcColor, 2));
    painter->setBrush(Qt::NoBrush);
    painter->drawArc(rect1, start * 16, span * 16);
    painter->drawArc(rect2, start * 16, span * 16);
    painter->restore();
}

void HArcGauge::drawPointer(QPainter *painter, int /*radius*/)
{
    Q_D(HArcGauge);
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(d->pointerColor);
    painter->setOpacity(0.8);
    painter->rotate(d->angleStart);
    painter->rotate(toAngle(d->currentValue));
    if (d->pointerStyle == HControlType::PointerStyle_Circle)
        drawPointerCircle(painter);
    if (d->pointerStyle == HControlType::PointerStyle_Indicator)
        drawPointerIndicator(painter);
    if (d->pointerStyle == HControlType::PointerStyle_IndicatorR)
        drawPointerIndicatorR(painter);
    if (d->pointerStyle == HControlType::PointerStyle_Triangle)
        drawPointerTriangle(painter);
    drawPointerCenter(painter);
    painter->restore();
}

void HArcGauge::drawPointerCircle(QPainter *painter)
{
    auto radius = 8;
    auto offset = 30;
    painter->drawEllipse(-radius, radius + offset, radius * 2, radius * 2);
}

void HArcGauge::drawPointerIndicator(QPainter *painter)
{
    auto radius = 75;
    auto poly = QPolygon() << QPoint(-5, 0) << QPoint(5, 0) << QPoint(0, radius);
    painter->drawConvexPolygon(poly);
}

void HArcGauge::drawPointerIndicatorR(QPainter *painter)
{
    Q_D(HArcGauge);
    auto radius = 75;
    auto poly = QPolygon() << QPoint(-5, 0) << QPoint(5, 0) << QPoint(0, radius);
    painter->setPen(QPen(d->pointerColor, 1));
    painter->setOpacity(1.0);
    painter->drawConvexPolygon(poly);
    // 增加绘制圆角直线,与之前三角形重叠,形成圆角指针
    painter->setPen(QPen(d->pointerColor, 4, Qt::SolidLine, Qt::RoundCap));
    painter->drawLine(0, 0, 0, radius);
}

void HArcGauge::drawPointerTriangle(QPainter *painter)
{
    auto radius = 10;
    auto offset = 55;
    auto poly = QPolygon() << QPoint(-5, offset) << QPoint(5, offset) << QPoint(0, radius + offset);
    painter->drawConvexPolygon(poly);
}

void HArcGauge::drawPointerCenter(QPainter *painter)
{
    auto radius = 12;
    painter->setOpacity(0.5);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    radius -= 4;
    painter->setOpacity(1.0);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
}

HE_CONTROL_END_NAMESPACE
