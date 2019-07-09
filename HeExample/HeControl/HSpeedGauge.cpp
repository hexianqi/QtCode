#include "HSpeedGauge_p.h"
#include <QtCore/QtMath>
#include <QtGui/QPainter>

HE_CONTROL_BEGIN_NAMESPACE

HSpeedGauge::HSpeedGauge(QWidget *parent) :
    HAnimationProgress(*new HSpeedGaugePrivate, parent)
{
}

HSpeedGauge::HSpeedGauge(HSpeedGaugePrivate &p, QWidget *parent) :
    HAnimationProgress(p, parent)
{
}

HSpeedGauge::~HSpeedGauge()
{
}

QSize HSpeedGauge::sizeHint() const
{
    return QSize(200, 200);
}

QSize HSpeedGauge::minimumSizeHint() const
{
    return QSize(40, 40);
}

int HSpeedGauge::scaleMajor() const
{
    Q_D(const HSpeedGauge);
    return d->scaleMajor;
}

int HSpeedGauge::scaleMinor() const
{
    Q_D(const HSpeedGauge);
    return d->scaleMinor;
}

int HSpeedGauge::angleStart() const
{
    Q_D(const HSpeedGauge);
    return d->angleStart;
}

int HSpeedGauge::angleEnd() const
{
    Q_D(const HSpeedGauge);
    return d->angleEnd;
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

QColor HSpeedGauge::pointerColor() const
{
    Q_D(const HSpeedGauge);
    return d->pointerColor;
}

QColor HSpeedGauge::textColor() const
{
    Q_D(const HSpeedGauge);
    return d->textColor;
}

void HSpeedGauge::setDecimal(int value)
{
    if (value > 2)
        return;
    HAnimationProgress::setDecimal(value);
}

void HSpeedGauge::setScaleMajor(int value)
{
    Q_D(HSpeedGauge);
    if (d->scaleMajor == value)
        return;
    d->scaleMajor = value;
    update();
}

void HSpeedGauge::setScaleMinor(int value)
{
    Q_D(HSpeedGauge);
    if (d->scaleMinor == value)
        return;
    d->scaleMinor = value;
    update();
}

void HSpeedGauge::setAngleStart(int value)
{
    Q_D(HSpeedGauge);
    if (d->angleStart == value)
        return;
    d->angleStart = value;
    update();
}

void HSpeedGauge::setAngleEnd(int value)
{
    Q_D(HSpeedGauge);
    if (d->angleEnd == value)
        return;
    d->angleEnd = value;
    update();
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

void HSpeedGauge::setPointerColor(const QColor &value)
{
    Q_D(HSpeedGauge);
    if (d->pointerColor == value)
        return;
    d->pointerColor = value;
    update();
}

void HSpeedGauge::setTextColor(const QColor &value)
{
    Q_D(HSpeedGauge);
    if (d->textColor == value)
        return;
    d->textColor = value;
    update();
}

void HSpeedGauge::paintEvent(QPaintEvent *)
{
    auto side = qMin(width(), height());
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    painter.translate(width() / 2, height() / 2);
    painter.scale(side / 200.0, side / 200.0);
    drawRing(&painter);
    drawScale(&painter);
    drawScaleLabel(&painter);
    drawPointer(&painter);
    drawValue(&painter);
}

void HSpeedGauge::drawRing(QPainter *painter)
{
    Q_D(HSpeedGauge);
    auto radius = 100 - d->ringWidth;
    auto rect = QRectF(-radius, -radius, radius * 2, radius * 2);
    auto sum = d->ringStart + d->ringMid + d->ringEnd;
    auto angleStart = angleSpan() * d->ringStart / sum;
    auto angleMid = angleSpan() * d->ringMid / sum;
    auto angleEnd = angleSpan() * d->ringEnd / sum;

    QPen pen;
    pen.setCapStyle(Qt::FlatCap);
    pen.setWidthF(d->ringWidth);
    painter->save();
    pen.setColor(d->ringColorStart);
    painter->setPen(pen);
    painter->drawArc(rect, (270 - d->angleStart - angleStart) * 16, angleStart * 16);
    pen.setColor(d->ringColorMid);
    painter->setPen(pen);
    painter->drawArc(rect, (270 - d->angleStart - angleStart - angleMid) * 16, angleMid * 16);
    pen.setColor(d->ringColorEnd);
    painter->setPen(pen);
    painter->drawArc(rect, (270 - d->angleStart - angleStart - angleMid - angleEnd) * 16, angleEnd * 16);
    painter->restore();
}

void HSpeedGauge::drawScale(QPainter *painter)
{
    Q_D(HSpeedGauge);
    auto radius = 94;
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
            painter->drawLine(0, radius - 13, 0, radius);
        }
        else
        {
            pen.setWidthF(0.5);
            painter->setPen(pen);
            painter->drawLine(0, radius - 5, 0, radius);
        }
        painter->rotate(angle);
    }
    painter->restore();
}

void HSpeedGauge::drawScaleLabel(QPainter *painter)
{
    Q_D(HSpeedGauge);
    auto radius = 70;
    auto start = qDegreesToRadians(270.0 - d->angleStart);
    auto delta = qDegreesToRadians(angleSpan()) / d->scaleMajor;
    painter->save();
    painter->setPen(d->textColor);
    for (int i = 0; i <= d->scaleMajor; i++)
    {
        auto angle = start - i * delta;
        auto value = fromRatio(1.0 * i / d->scaleMajor);
        auto text = QString::number(value, 'f', d->decimal);
        auto textWidth = fontMetrics().width(text);
        auto textHeight = fontMetrics().height();
        auto x = radius * qCos(angle) - textWidth / 2;
        auto y = -radius * qSin(angle) + textHeight / 4;
        painter->drawText(QPointF(x, y), text);
    }
    painter->restore();
}

void HSpeedGauge::drawPointer(QPainter *painter)
{
    Q_D(HSpeedGauge);
    auto radius = 62;
    QPolygon pts;
    pts.setPoints(4, -5, 0, 0, -8, 5, 0, 0, radius);
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(d->pointerColor);
    painter->rotate(d->angleStart);
    painter->rotate(toAngle(d->currentValue));
    painter->drawConvexPolygon(pts);
    painter->restore();
}

void HSpeedGauge::drawValue(QPainter *painter)
{
    Q_D(HSpeedGauge);
    auto radius = 100;
    auto rect = QRectF(-radius, radius / 3, radius * 2, radius / 2);
    auto text = QString::number(d->currentValue, 'f', d->decimal);
    auto f = font();
    f.setPixelSize(qMin(width() * 0.1, height() * 0.1));
    f.setBold(true);

    painter->save();
    painter->setPen(d->textColor);
    painter->setFont(f);
    painter->drawText(rect, Qt::AlignCenter, text);
    painter->restore();
}

double HSpeedGauge::angleSpan()
{
    Q_D(HSpeedGauge);
    return 360.0 - d->angleStart - d->angleEnd;
}

double HSpeedGauge::toAngle(double value)
{
    return angleSpan() * toRatio(value);
}

HE_CONTROL_END_NAMESPACE
