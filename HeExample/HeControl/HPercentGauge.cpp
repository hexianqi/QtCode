#include "HPercentGauge_p.h"
#include <QtGui/QPainter>

HE_BEGIN_NAMESPACE

HPercentGaugePrivate::HPercentGaugePrivate()
{
    angleStart = 60;
    angleEnd = 60;
    textColor = QColor(34, 163, 169, 255);
    scaleColor = QColor(34, 163, 169, 100);
    scaleLabelColor = QColor(34, 163, 169, 200);
}

HPercentGauge::HPercentGauge(QWidget *parent) :
    HCircleGauge(*new HPercentGaugePrivate, parent)
{
}

HPercentGauge::HPercentGauge(HPercentGaugePrivate &p, QWidget *parent) :
    HCircleGauge(p, parent)
{
}

QColor HPercentGauge::baseColor() const
{
    Q_D(const HPercentGauge);
    return d->baseColor;
}

QColor HPercentGauge::arcColor() const
{
    Q_D(const HPercentGauge);
    return d->arcColor;
}

QColor HPercentGauge::titleColor() const
{
    Q_D(const HPercentGauge);
    return d->titleColor;
}

QString HPercentGauge::title() const
{
    Q_D(const HPercentGauge);
    return d->title;
}

void HPercentGauge::setBaseColor(const QColor &value)
{
    Q_D(HPercentGauge);
    if (d->baseColor == value)
        return;
    d->baseColor = value;
    d->arcColor = d->baseColor;
    d->titleColor = d->baseColor;
    d->textColor = d->baseColor;
    d->baseColor.setAlpha(100);
    d->scaleColor = d->baseColor;
    d->baseColor.setAlpha(200);
    d->scaleLabelColor = d->baseColor;
    d->baseColor = value;
    update();
}

void HPercentGauge::setArcColor(const QColor &value)
{
    Q_D(HPercentGauge);
    if (d->arcColor == value)
        return;
    d->arcColor = value;
    update();
}

void HPercentGauge::setTitleColor(const QColor &value)
{
    Q_D(HPercentGauge);
    if (d->titleColor == value)
        return;
    d->titleColor = value;
    update();
}

void HPercentGauge::setTitle(const QString &value)
{
    Q_D(HPercentGauge);
    if (d->title == value)
        return;
    d->title = value;
    update();
}

void HPercentGauge::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    preDraw(&painter);
    // 绘制背景
    drawBackground(&painter);
    // 绘制进度条
    drawProgress(&painter, 95);
    // 绘制圆弧进度小球
    drawPointer(&painter, 100);
    // 绘制刻度线
    drawScale(&painter, 90);
    // 绘制刻度值
    drawScaleLabel(&painter, 70);
    // 绘制当前值
    drawValue(&painter, 100);
    // 绘制标题
    drawTitle(&painter);
}

void HPercentGauge::drawProgress(QPainter *painter, int radius)
{
    Q_D(HPercentGauge);
    auto rect = QRectF(-radius, -radius, radius * 2, radius * 2);
    auto current = static_cast<int>(toAngle(d->currentValue));
    auto other = static_cast<int>(toAngle(d->maximum - d->currentValue));
    painter->save();
    painter->setBrush(Qt::NoBrush);
    painter->setPen(QPen(d->arcColor, 5, Qt::SolidLine, Qt::RoundCap));
    painter->drawArc(rect, (270 - d->angleStart - current) * 16, current * 16);
    painter->setPen(QPen(d->scaleColor, 5, Qt::SolidLine, Qt::RoundCap));
    painter->drawArc(rect, (270 - d->angleStart - current - other) * 16, other * 16);
    painter->restore();
}

void HPercentGauge::drawPointer(QPainter *painter, int /*radius*/)
{
    Q_D(HPercentGauge);
    auto radius = 5;
    auto offset = 85;
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(d->arcColor);
    painter->rotate(d->angleStart);
    painter->rotate(toAngle(d->currentValue));
    painter->drawEllipse(-radius, radius + offset, radius * 2, radius * 2);
    painter->restore();
}

void HPercentGauge::drawTitle(QPainter *painter)
{
    Q_D(HPercentGauge);
    if (d->title.isEmpty())
        return;
    auto radius = 100;
    auto f = font();
    f.setPixelSize(20);
    auto rect = QRectF(-radius, radius / 3.0, radius * 2, radius / 3.0);
    painter->save();
    painter->setPen(d->titleColor);
    painter->setFont(f);
    painter->drawText(rect, Qt::AlignCenter, d->title);
    painter->restore();
}

HE_END_NAMESPACE
