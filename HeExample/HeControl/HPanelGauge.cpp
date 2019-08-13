#include "HPanelGauge_p.h"
#include <QtGui/QPainter>

HE_CONTROL_BEGIN_NAMESPACE

HPanelGauge::HPanelGauge(QWidget *parent) :
    HCircleGauge(*new HPanelGaugePrivate, parent)
{
}

HPanelGauge::HPanelGauge(HPanelGaugePrivate &p, QWidget *parent) :
    HCircleGauge(p, parent)
{
}

HPanelGauge::~HPanelGauge()
{
}

int HPanelGauge::ringWidth() const
{
    Q_D(const HPanelGauge);
    return d->ringWidth;
}

QColor HPanelGauge::ringColor() const
{
    Q_D(const HPanelGauge);
    return d->ringColor;
}

QString HPanelGauge::unit() const
{
    Q_D(const HPanelGauge);
    return d->unit;
}

QString HPanelGauge::text() const
{
    Q_D(const HPanelGauge);
    return d->text;
}

void HPanelGauge::setRingWidth(int value)
{
    Q_D(HPanelGauge);
    if (d->ringWidth == value)
        return;
    d->ringWidth = value;
    update();
}

void HPanelGauge::setRingColor(const QColor &value)
{
    Q_D(HPanelGauge);
    if (d->ringColor == value)
        return;
    d->ringColor = value;
    update();
}

void HPanelGauge::setUnit(const QString &value)
{
    Q_D(HPanelGauge);
    if (d->unit == value)
        return;
    d->unit = value;
    update();
}

void HPanelGauge::setText(const QString &value)
{
    Q_D(HPanelGauge);
    if (d->text == value)
        return;
    d->text = value;
    update();
}

void HPanelGauge::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    preDraw(&painter);
    drawBackground(&painter);
    drawProgress(&painter, 70);
    drawScale(&painter, 72);
    drawScaleLabel(&painter, 95);
    drawPointer(&painter, 70);
    drawValue(&painter, 100);
}

void HPanelGauge::drawProgress(QPainter *painter, int radius)
{
    Q_D(HPanelGauge);
    radius = radius - d->ringWidth;
    auto rect = QRectF(-radius, -radius, radius * 2, radius * 2);
    painter->save();
    painter->setPen(QPen(d->ringColor, d->ringWidth, Qt::SolidLine, Qt::FlatCap));
    painter->drawArc(rect, (270 - d->angleStart - angleSpan()) * 16, angleSpan() * 16);
    painter->restore();
}

void HPanelGauge::drawScale(QPainter *painter, int radius)
{
    Q_D(HPanelGauge);
    auto steps = d->scaleMajor * d->scaleMinor;
    auto angle = angleSpan() / steps;
    auto pen1 = QPen(d->scaleColor, 1.5, Qt::SolidLine, Qt::RoundCap);
    auto pen2 = QPen(d->scaleColor, 0.5, Qt::SolidLine, Qt::RoundCap);
    painter->save();
    painter->rotate(d->angleStart);
    for (int i = 0; i <= steps; i++)
    {
        if (i % d->scaleMinor == 0)
        {
            painter->setPen(pen1);
            painter->drawLine(0, radius, 0, radius + 13);
        }
        else
        {
            painter->setPen(pen2);
            painter->drawLine(0, radius, 0, radius + 5);
        }
        painter->rotate(angle);
    }
    painter->restore();
}

void HPanelGauge::drawValue(QPainter *painter, int radius)
{
    Q_D(HPanelGauge);
    auto f1 = font();
    f1.setPixelSize(15);
    auto f2 = font();
    f2.setPixelSize(12);
    auto rect1 = QRectF(-radius, radius / 3.5, radius * 2, radius / 3.5);
    auto rect2 = QRectF(-radius, radius / 2.5, radius * 2, radius / 2.5);
    auto text1 = QString::number(d->currentValue, 'f', d->decimal);
    if (!d->unit.isEmpty())
        text1 += " " + d->unit;
    auto text2 = d->text;
    painter->save();
    painter->setPen(d->textColor);
    painter->setFont(f1);
    painter->drawText(rect1, Qt::AlignCenter, text1);
    painter->setFont(f2);
    painter->drawText(rect2, Qt::AlignCenter, text2);
    painter->restore();
}

HE_CONTROL_END_NAMESPACE
