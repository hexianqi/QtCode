#include "HSpeedGauge_p.h"
#include <QtGui/QPainter>

HE_BEGIN_NAMESPACE

HSpeedGaugePrivate::HSpeedGaugePrivate()
{
    scaleMajor = 8;
    scaleMinor = 1;
    angleStart = 50;
    angleEnd = 50;
    pointerColor = QColor(178, 221, 253);
    textColor = QColor(50, 50, 50);
}

HSpeedGauge::HSpeedGauge(QWidget *parent) :
    HCircleGauge(*new HSpeedGaugePrivate, parent)
{
}

HSpeedGauge::HSpeedGauge(HSpeedGaugePrivate &p, QWidget *parent) :
    HCircleGauge(p, parent)
{
}

int HSpeedGauge::ringWidth() const
{
    Q_D(const HSpeedGauge);
    return d->ringWidth;
}

int HSpeedGauge::ringPercentStart() const
{
    Q_D(const HSpeedGauge);
    return d->ringStart;
}

int HSpeedGauge::ringPercentMid() const
{
    Q_D(const HSpeedGauge);
    return d->ringMid;
}

int HSpeedGauge::ringPercentEnd() const
{
    Q_D(const HSpeedGauge);
    return d->ringEnd;
}

QColor HSpeedGauge::ringColorStart() const
{
    Q_D(const HSpeedGauge);
    return d->ringColorStart;
}

QColor HSpeedGauge::ringColorMid() const
{
    Q_D(const HSpeedGauge);
    return d->ringColorMid;
}

QColor HSpeedGauge::ringColorEnd() const
{
    Q_D(const HSpeedGauge);
    return d->ringColorEnd;
}

void HSpeedGauge::setRingWidth(int value)
{
    Q_D(HSpeedGauge);
    if (d->ringWidth == value)
        return;
    d->ringWidth = value;
    update();
}

void HSpeedGauge::setRingPercentStart(int value)
{
    Q_D(HSpeedGauge);
    if (d->ringStart == value)
        return;
    d->ringStart = value;
    update();
}

void HSpeedGauge::setRingPercentMid(int value)
{
    Q_D(HSpeedGauge);
    if (d->ringMid == value)
        return;
    d->ringMid = value;
    update();
}

void HSpeedGauge::setRingPercentEnd(int value)
{
    Q_D(HSpeedGauge);
    if (d->ringEnd == value)
        return;
    d->ringEnd = value;
    update();
}

void HSpeedGauge::setRingColorStart(const QColor &value)
{
    Q_D(HSpeedGauge);
    if (d->ringColorStart == value)
        return;
    d->ringColorStart = value;
    update();
}

void HSpeedGauge::setRingColorMid(const QColor &value)
{
    Q_D(HSpeedGauge);
    if (d->ringColorMid == value)
        return;
    d->ringColorMid = value;
    update();
}

void HSpeedGauge::setRingColorEnd(const QColor &value)
{
    Q_D(HSpeedGauge);
    if (d->ringColorEnd == value)
        return;
    d->ringColorEnd = value;
    update();
}

void HSpeedGauge::paintEvent(QPaintEvent *)
{
    Q_D(HSpeedGauge);
    QPainter painter(this);
    preDraw(&painter);
    drawProgress(&painter, 100 - d->ringWidth);
    drawScale(&painter, 94);
    drawScaleLabel(&painter, 70);
    drawPointer(&painter, 62);
    drawValue(&painter, 100);
}

void HSpeedGauge::drawProgress(QPainter *painter, int radius)
{
    Q_D(HSpeedGauge);
    auto rect = QRectF(-radius, -radius, radius * 2, radius * 2);
    auto sum = d->ringStart + d->ringMid + d->ringEnd;
    auto start = static_cast<int>(angleSpan() * d->ringStart / sum);
    auto mid = static_cast<int>(angleSpan() * d->ringMid / sum);
    auto end = static_cast<int>(angleSpan() * d->ringEnd / sum);

    QPen pen;
    pen.setCapStyle(Qt::FlatCap);
    pen.setWidthF(d->ringWidth);
    painter->save();
    pen.setColor(d->ringColorStart);
    painter->setPen(pen);
    painter->drawArc(rect, (270 - d->angleStart - start) * 16, start * 16);
    pen.setColor(d->ringColorMid);
    painter->setPen(pen);
    painter->drawArc(rect, (270 - d->angleStart - start - mid) * 16, mid * 16);
    pen.setColor(d->ringColorEnd);
    painter->setPen(pen);
    painter->drawArc(rect, (270 - d->angleStart - start - mid - end) * 16, end * 16);
    painter->restore();
}

void HSpeedGauge::drawScale(QPainter *painter, int radius)
{
    Q_D(HSpeedGauge);
    auto sum = d->ringStart + d->ringMid + d->ringEnd;
    auto steps = d->scaleMajor * d->scaleMinor;
    auto angle = angleSpan() / steps;
    auto indexStart = steps * d->ringStart / sum + 1;
    auto indexMid = steps * d->ringMid / sum - 1;
    auto indexEnd = steps * d->ringEnd / sum + 1;
    auto index = 0;
    QPen pen;
    pen.setColor(d->textColor);
    pen.setCapStyle(Qt::RoundCap);

    painter->save();
    painter->rotate(d->angleStart);
    for (int i = 0; i <= steps; i++)
    {
        if (i % d->scaleMinor == 0)
        {
            if (index < indexStart)
                pen.setColor(d->ringColorStart);
            else if (index < (indexStart + indexMid))
                pen.setColor(d->ringColorMid);
            else if (index < (indexStart + indexMid + indexEnd))
                pen.setColor(d->ringColorEnd);

            index++;
            pen.setWidthF(1.5);
            painter->setPen(pen);
            painter->drawLine(0, radius, 0, radius - 13);
        }
        else
        {
            pen.setWidthF(0.5);
            painter->setPen(pen);
            painter->drawLine(0, radius, 0, radius - 5);
        }
        painter->rotate(angle);
    }
    painter->restore();
}

HE_END_NAMESPACE
