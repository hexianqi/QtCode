#include "HGaugeArc_p.h"
#include <QtGui/QPainter>
#include <QtCore/QtMath>

HE_CONTROL_BEGIN_NAMESPACE

HGaugeArc::HGaugeArc(QWidget *parent) :
    HAnimationProgress(*new HGaugeArcPrivate, parent)
{
}

HGaugeArc::HGaugeArc(HGaugeArcPrivate &p, QWidget *parent) :
    HAnimationProgress(p, parent)
{
}

HGaugeArc::~HGaugeArc()
{
}

QSize HGaugeArc::sizeHint() const
{
    return QSize(200, 200);
}

QSize HGaugeArc::minimumSizeHint() const
{
    return QSize(40, 40);
}

int HGaugeArc::scaleMajor() const
{
    Q_D(const HGaugeArc);
    return d->scaleMajor;
}

int HGaugeArc::scaleMinor() const
{
    Q_D(const HGaugeArc);
    return d->scaleMinor;
}

int HGaugeArc::angleStart() const
{
    Q_D(const HGaugeArc);
    return d->angleStart;
}

int HGaugeArc::angleEnd() const
{
    Q_D(const HGaugeArc);
    return d->angleEnd;
}

QColor HGaugeArc::arcColor() const
{
    Q_D(const HGaugeArc);
    return d->arcColor;
}

QColor HGaugeArc::scaleColor() const
{
    Q_D(const HGaugeArc);
    return d->scaleColor;
}

QColor HGaugeArc::scaleLabelColor() const
{
    Q_D(const HGaugeArc);
    return d->scaleLabelColor;
}

QColor HGaugeArc::textColor() const
{
    Q_D(const HGaugeArc);
    return d->textColor;
}

QColor HGaugeArc::pointerColor() const
{
    Q_D(const HGaugeArc);
    return d->pointerColor;
}

HGaugeArc::PointerStyle HGaugeArc::pointerStyle() const
{
    Q_D(const HGaugeArc);
    return d->pointerStyle;
}

void HGaugeArc::setScaleMajor(int value)
{
    Q_D(HGaugeArc);
    if (d->scaleMajor == value)
        return;
    d->scaleMajor = value;
    update();
}

void HGaugeArc::setScaleMinor(int value)
{
    Q_D(HGaugeArc);
    if (d->scaleMinor == value)
        return;
    d->scaleMinor = value;
    update();
}

void HGaugeArc::setAngleStart(int value)
{
    Q_D(HGaugeArc);
    if (d->angleStart == value)
        return;
    d->angleStart = value;
    d->angleRange = 360 - value - d->angleEnd;
    update();
}

void HGaugeArc::setAngleEnd(int value)
{
    Q_D(HGaugeArc);
    if (d->angleEnd == value)
        return;
    d->angleEnd = value;
    d->angleRange = 360 - value - d->angleStart;
    update();
}

void HGaugeArc::setArcColor(const QColor &value)
{
    Q_D(HGaugeArc);
    if (d->arcColor == value)
        return;
    d->arcColor = value;
    update();
}

void HGaugeArc::setScaleColor(const QColor &value)
{
    Q_D(HGaugeArc);
    if (d->scaleColor == value)
        return;
    d->scaleColor = value;
    update();
}

void HGaugeArc::setScaleLabelColor(const QColor &value)
{
    Q_D(HGaugeArc);
    if (d->scaleLabelColor == value)
        return;
    d->scaleLabelColor = value;
    update();
}

void HGaugeArc::setTextColor(const QColor &value)
{
    Q_D(HGaugeArc);
    if (d->textColor == value)
        return;
    d->textColor = value;
    update();
}

void HGaugeArc::setPointerColor(const QColor &value)
{
    Q_D(HGaugeArc);
    if (d->pointerColor == value)
        return;
    d->pointerColor = value;
    update();
}

void HGaugeArc::setPointerStyle(PointerStyle value)
{
    Q_D(HGaugeArc);
    if (d->pointerStyle == value)
        return;
    d->pointerStyle = value;
    update();
}

void HGaugeArc::paintEvent(QPaintEvent *)
{
    // 绘制准备工作,启用反锯齿,平移坐标轴中心,等比例缩放
    auto side = qMin(width(), height());
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    painter.translate(width() / 2, height() / 2);
    painter.scale(side / 200.0, side / 200.0);
    // 绘制圆弧
    drawArc(&painter);
    // 绘制刻度线
    drawScale(&painter);
    // 绘制刻度值
    drawScaleLabel(&painter);
    // 绘制指示器
    drawPointer(&painter);
    // 绘制指针中心圆外边框
    drawRoundCircle(&painter);
    // 绘制指针中心圆
    drawCenterCircle(&painter);
    // 绘制当前值
    drawValue(&painter);
}

void HGaugeArc::drawArc(QPainter *painter)
{
    Q_D(HGaugeArc);
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

void HGaugeArc::drawScale(QPainter *painter)
{
    Q_D(HGaugeArc);
    auto radius = 97;
    auto steps = d->scaleMajor * d->scaleMinor;
    auto angle = 1.0 * d->angleRange / steps;
    auto pen = QPen();
    pen.setColor(d->scaleColor);
    pen.setCapStyle(Qt::RoundCap);
    painter->save();
    painter->rotate(d->angleStart);
    for (int i = 0; i <= steps; i++)
    {
        if (i % d->scaleMinor == 0)
        {
            pen.setWidthF(1.5);
            painter->setPen(pen);
            painter->drawLine(0, radius - 12, 0, radius);
        }
        else
        {
            pen.setWidthF(1.0);
            painter->setPen(pen);
            painter->drawLine(0, radius - 5, 0, radius);
        }
        painter->rotate(angle);
    }
    painter->restore();
}

void HGaugeArc::drawScaleLabel(QPainter *painter)
{
    Q_D(HGaugeArc);
    auto radius = 75;
    auto start = qDegreesToRadians(270.0 - d->angleStart);
    auto delta = qDegreesToRadians(1.0 * d->angleRange) / d->scaleMajor;
    painter->save();
    painter->setPen(d->scaleLabelColor);
    for (int i = 0; i <= d->scaleMajor; i++)
    {
        auto angle = start - i * delta;
        auto value = 1.0 * i * (d->maximum - d->minimum) / d->scaleMajor + d->minimum;
        auto text = QString::number(value, 'f', d->decimal);
        auto textWidth = fontMetrics().width(text);
        auto textHeight = fontMetrics().height();
        auto x = radius * qCos(angle) - textWidth / 2;
        auto y = -radius * qSin(angle) + textHeight / 4;
        painter->drawText(QPointF(x, y), text);
    }
    painter->restore();
}

void HGaugeArc::drawPointer(QPainter *painter)
{
    Q_D(HGaugeArc);
    if (d->pointerStyle == Circle)
        drawPointerCircle(painter);
    if (d->pointerStyle == Indicator)
        drawPointerIndicator(painter);
    if (d->pointerStyle == IndicatorR)
        drawPointerIndicatorR(painter);
    if (d->pointerStyle == Triangle)
        drawPointerTriangle(painter);
}

void HGaugeArc::drawPointerCircle(QPainter *painter)
{
    Q_D(HGaugeArc);
    auto radius = 8;
    auto offset = 30;
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(d->pointerColor);
    painter->rotate(d->angleStart);
    painter->rotate(toAngle(d->currentValue));
    painter->drawEllipse(-radius, radius + offset, radius * 2, radius * 2);
    painter->restore();
}

void HGaugeArc::drawPointerIndicator(QPainter *painter)
{
    Q_D(HGaugeArc);
    auto radius = 75;
    auto poly = QPolygon() << QPoint(-5, 0) << QPoint(5, 0) << QPoint(0, radius);
    painter->save();
    painter->setOpacity(0.8);
    painter->setPen(Qt::NoPen);
    painter->setBrush(d->pointerColor);
    painter->rotate(d->angleStart);
    painter->rotate(toAngle(d->currentValue));
    painter->drawConvexPolygon(poly);
    painter->restore();
}

void HGaugeArc::drawPointerIndicatorR(QPainter *painter)
{
    Q_D(HGaugeArc);
    auto radius = 75;
    auto poly = QPolygon() << QPoint(-5, 0) << QPoint(5, 0) << QPoint(0, radius);
    auto pen = QPen();
    pen.setWidthF(1);
    pen.setColor(d->pointerColor);
    painter->save();
    painter->setPen(pen);
    painter->setBrush(d->pointerColor);
    painter->rotate(d->angleStart);
    painter->rotate(toAngle(d->currentValue));
    painter->drawConvexPolygon(poly);
    // 增加绘制圆角直线,与之前三角形重叠,形成圆角指针
    pen.setCapStyle(Qt::RoundCap);
    pen.setWidthF(4);
    painter->setPen(pen);
    painter->drawLine(0, 0, 0, radius);
    painter->restore();
}

void HGaugeArc::drawPointerTriangle(QPainter *painter)
{
    Q_D(HGaugeArc);
    auto radius = 10;
    auto offset = 55;
    auto poly = QPolygon() << QPoint(-5, offset) << QPoint(5, offset) << QPoint(0, radius + offset);
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(d->pointerColor);
    painter->rotate(d->angleStart);
    painter->rotate(toAngle(d->currentValue));
    painter->drawConvexPolygon(poly);
    painter->restore();
}

void HGaugeArc::drawRoundCircle(QPainter *painter)
{
    Q_D(HGaugeArc);
    auto radius = 12;
    painter->save();
    painter->setOpacity(0.5);
    painter->setPen(Qt::NoPen);
    painter->setBrush(d->pointerColor);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    painter->restore();
}
void HGaugeArc::drawCenterCircle(QPainter *painter)
{
    Q_D(HGaugeArc);
    auto radius = 8;
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(d->pointerColor);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    painter->restore();
}

void HGaugeArc::drawValue(QPainter *painter)
{
    Q_D(HGaugeArc);
    auto radius = 100;
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

double HGaugeArc::angleRange()
{
    Q_D(HGaugeArc);
    return d->angleRange;
}

double HGaugeArc::toAngle(double value)
{
    Q_D(HGaugeArc);
    return d->angleRange * toRatio(value);
}

HE_CONTROL_END_NAMESPACE
