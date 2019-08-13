#include "HCircleGauge_p.h"
#include <QtCore/QtMath>
#include <QtGui/QPainter>

HE_CONTROL_BEGIN_NAMESPACE

HCircleGauge::HCircleGauge(QWidget *parent) :
    HAnimationProgress(*new HCircleGaugePrivate, parent)
{
}

HCircleGauge::HCircleGauge(HCircleGaugePrivate &p, QWidget *parent) :
    HAnimationProgress(p, parent)
{
}

HCircleGauge::~HCircleGauge()
{
}

QSize HCircleGauge::sizeHint() const
{
    return QSize(200, 200);
}

QSize HCircleGauge::minimumSizeHint() const
{
    return QSize(40, 40);
}

int HCircleGauge::scaleMajor() const
{
    Q_D(const HCircleGauge);
    return d->scaleMajor;
}

int HCircleGauge::scaleMinor() const
{
    Q_D(const HCircleGauge);
    return d->scaleMinor;
}

int HCircleGauge::scaleDecimal() const
{
    Q_D(const HCircleGauge);
    return d->scaleDecimal;
}

int HCircleGauge::angleStart() const
{
    Q_D(const HCircleGauge);
    return d->angleStart;
}

int HCircleGauge::angleEnd() const
{
    Q_D(const HCircleGauge);
    return d->angleEnd;
}

QColor HCircleGauge::pointerColor() const
{
    Q_D(const HCircleGauge);
    return d->pointerColor;
}

QColor HCircleGauge::background() const
{
    Q_D(const HCircleGauge);
    return d->background;
}

QColor HCircleGauge::textColor() const
{
    Q_D(const HCircleGauge);
    return d->textColor;
}

QColor HCircleGauge::scaleColor() const
{
    Q_D(const HCircleGauge);
    return d->scaleColor;
}

QColor HCircleGauge::scaleLabelColor() const
{
    Q_D(const HCircleGauge);
    return d->scaleLabelColor;
}

void HCircleGauge::setDecimal(int value)
{
    if (value > 2)
        return;
    HAnimationProgress::setDecimal(value);
}

void HCircleGauge::setScaleMajor(int value)
{
    Q_D(HCircleGauge);
    if (d->scaleMajor == value)
        return;
    d->scaleMajor = value;
    update();
}

void HCircleGauge::setScaleMinor(int value)
{
    Q_D(HCircleGauge);
    if (d->scaleMinor == value)
        return;
    d->scaleMinor = value;
    update();
}

void HCircleGauge::setScaleDecimal(int value)
{
    Q_D(HCircleGauge);
    if (d->scaleDecimal == value)
        return;
    d->scaleDecimal = value;
    update();
}

void HCircleGauge::setAngleStart(int value)
{
    Q_D(HCircleGauge);
    if (d->angleStart == value)
        return;
    d->angleStart = value;
    update();
}

void HCircleGauge::setAngleEnd(int value)
{
    Q_D(HCircleGauge);
    if (d->angleEnd == value)
        return;
    d->angleEnd = value;
    update();
}

void HCircleGauge::setBackground(const QColor &value)
{
    Q_D(HCircleGauge);
    if (d->background == value)
        return;
    d->background = value;
    update();
}

void HCircleGauge::setPointerColor(const QColor &value)
{
    Q_D(HCircleGauge);
    if (d->pointerColor == value)
        return;
    d->pointerColor = value;
    update();
}

void HCircleGauge::setTextColor(const QColor &value)
{
    Q_D(HCircleGauge);
    if (d->textColor == value)
        return;
    d->textColor = value;
    update();
}

void HCircleGauge::setScaleColor(const QColor &value)
{
    Q_D(HCircleGauge);
    if (d->scaleColor == value)
        return;
    d->scaleColor = value;
    update();
}

void HCircleGauge::setScaleLabelColor(const QColor &value)
{
    Q_D(HCircleGauge);
    if (d->scaleLabelColor == value)
        return;
    d->scaleLabelColor = value;
    update();
}

void HCircleGauge::preDraw(QPainter *painter)
{
    // 绘制准备工作,启用反锯齿,平移坐标轴中心,等比例缩放
    auto side = qMin(width(), height());
    painter->setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    painter->translate(width() / 2, height() / 2);
    painter->scale(side / 200.0, side / 200.0);
}

void HCircleGauge::drawBackground(QPainter *painter)
{
    Q_D(HCircleGauge);
    if (d->background == Qt::transparent)
        return;
    auto radius = 99;
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->fillRect(-radius, -radius, radius * 2, radius * 2, d->background);
    painter->restore();
}

void HCircleGauge::drawScale(QPainter *painter, int radius)
{
    Q_D(HCircleGauge);
    auto steps = d->scaleMajor * d->scaleMinor;
    auto angle = angleSpan() / steps;
    auto pen1 = QPen(d->scaleColor, 1.5, Qt::SolidLine, Qt::RoundCap);
    auto pen2 = QPen(d->scaleColor, 1.0, Qt::SolidLine, Qt::RoundCap);
    painter->save();
    painter->rotate(d->angleStart);
    for (int i = 0; i <= steps; i++)
    {
        if (i % d->scaleMinor == 0)
        {
            painter->setPen(pen1);
            painter->drawLine(0, radius, 0, radius - 10);
        }
        else
        {
            painter->setPen(pen2);
            painter->drawLine(0, radius, 0, radius - 5);
        }
        painter->rotate(angle);
    }
    painter->restore();
}

void HCircleGauge::drawScaleLabel(QPainter *painter, int radius)
{
    Q_D(HCircleGauge);
    auto start = qDegreesToRadians(270.0 - d->angleStart);
    auto delta = qDegreesToRadians(angleSpan()) / d->scaleMajor;
    painter->save();
    painter->setPen(d->scaleLabelColor);
    for (int i = 0; i <= d->scaleMajor; i++)
    {
        auto angle = start - i * delta;
        auto value = fromRatio(1.0 * i / d->scaleMajor);
        auto text = QString::number(value, 'f', d->scaleDecimal);
        auto textWidth = fontMetrics().width(text);
        auto textHeight = fontMetrics().height();
        auto x = radius * qCos(angle) - textWidth / 2;
        auto y = -radius * qSin(angle) + textHeight / 4;
        painter->drawText(QPointF(x, y), text);
    }
    painter->restore();
}

void HCircleGauge::drawPointer(QPainter *painter, int radius)
{
    Q_D(HCircleGauge);
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

void HCircleGauge::drawValue(QPainter *painter, int radius)
{
    Q_D(HCircleGauge);
    auto f = font();
    f.setPixelSize(30);
    auto rect = QRectF(-radius, radius / 2, radius * 2, radius / 3);
    auto text = QString::number(d->currentValue, 'f', d->decimal);
    painter->save();
    painter->setPen(d->textColor);
    painter->setFont(f);
    painter->drawText(rect, Qt::AlignCenter, text);
    painter->restore();
}

double HCircleGauge::angleSpan()
{
    Q_D(HCircleGauge);
    return 360.0 - d->angleStart - d->angleEnd;
}

double HCircleGauge::toAngle(double value)
{
    return angleSpan() * toRatio(value);
}

HE_CONTROL_END_NAMESPACE
