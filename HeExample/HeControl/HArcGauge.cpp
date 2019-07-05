#include "HArcGauge_p.h"
#include <QtGui/QPainter>
#include <QtCore/QtMath>

HE_CONTROL_BEGIN_NAMESPACE

HArcGauge::HArcGauge(QWidget *parent) :
    HAnimationProgress(*new HArcGaugePrivate, parent)
{
}

HArcGauge::HArcGauge(HArcGaugePrivate &p, QWidget *parent) :
    HAnimationProgress(p, parent)
{
}

HArcGauge::~HArcGauge()
{
}

QSize HArcGauge::sizeHint() const
{
    return QSize(200, 200);
}

QSize HArcGauge::minimumSizeHint() const
{
    return QSize(40, 40);
}

int HArcGauge::scaleMajor() const
{
    Q_D(const HArcGauge);
    return d->scaleMajor;
}

int HArcGauge::scaleMinor() const
{
    Q_D(const HArcGauge);
    return d->scaleMinor;
}

int HArcGauge::angleStart() const
{
    Q_D(const HArcGauge);
    return d->angleStart;
}

int HArcGauge::angleEnd() const
{
    Q_D(const HArcGauge);
    return d->angleEnd;
}

QColor HArcGauge::arcColor() const
{
    Q_D(const HArcGauge);
    return d->arcColor;
}

QColor HArcGauge::scaleColor() const
{
    Q_D(const HArcGauge);
    return d->scaleColor;
}

QColor HArcGauge::scaleLabelColor() const
{
    Q_D(const HArcGauge);
    return d->scaleLabelColor;
}

QColor HArcGauge::textColor() const
{
    Q_D(const HArcGauge);
    return d->textColor;
}

QColor HArcGauge::pointerColor() const
{
    Q_D(const HArcGauge);
    return d->pointerColor;
}

HArcGauge::PointerStyle HArcGauge::pointerStyle() const
{
    Q_D(const HArcGauge);
    return d->pointerStyle;
}

void HArcGauge::setScaleMajor(int value)
{
    Q_D(HArcGauge);
    if (d->scaleMajor == value)
        return;
    d->scaleMajor = value;
    update();
}

void HArcGauge::setScaleMinor(int value)
{
    Q_D(HArcGauge);
    if (d->scaleMinor == value)
        return;
    d->scaleMinor = value;
    update();
}

void HArcGauge::setAngleStart(int value)
{
    Q_D(HArcGauge);
    if (d->angleStart == value)
        return;
    d->angleStart = value;
    update();
}

void HArcGauge::setAngleEnd(int value)
{
    Q_D(HArcGauge);
    if (d->angleEnd == value)
        return;
    d->angleEnd = value;
    update();
}

void HArcGauge::setArcColor(const QColor &value)
{
    Q_D(HArcGauge);
    if (d->arcColor == value)
        return;
    d->arcColor = value;
    update();
}

void HArcGauge::setScaleColor(const QColor &value)
{
    Q_D(HArcGauge);
    if (d->scaleColor == value)
        return;
    d->scaleColor = value;
    update();
}

void HArcGauge::setScaleLabelColor(const QColor &value)
{
    Q_D(HArcGauge);
    if (d->scaleLabelColor == value)
        return;
    d->scaleLabelColor = value;
    update();
}

void HArcGauge::setTextColor(const QColor &value)
{
    Q_D(HArcGauge);
    if (d->textColor == value)
        return;
    d->textColor = value;
    update();
}

void HArcGauge::setPointerColor(const QColor &value)
{
    Q_D(HArcGauge);
    if (d->pointerColor == value)
        return;
    d->pointerColor = value;
    update();
}

void HArcGauge::setPointerStyle(PointerStyle value)
{
    Q_D(HArcGauge);
    if (d->pointerStyle == value)
        return;
    d->pointerStyle = value;
    update();
}

void HArcGauge::paintEvent(QPaintEvent *)
{    
    auto side = qMin(width(), height());
    QPainter painter(this);
    // 绘制准备工作,启用反锯齿,平移坐标轴中心,等比例缩放
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

void HArcGauge::drawArc(QPainter *painter)
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

void HArcGauge::drawScale(QPainter *painter)
{
    Q_D(HArcGauge);
    auto radius = 97;
    auto steps = d->scaleMajor * d->scaleMinor;
    auto angle = angleSpan() / steps;
    auto pen1 = QPen(d->scaleColor, 1.5, Qt::SolidLine, Qt::RoundCap);
    auto pen2 = QPen(d->scaleColor, 1, Qt::SolidLine, Qt::RoundCap);
    painter->save();
    painter->rotate(d->angleStart);
    for (int i = 0; i <= steps; i++)
    {
        if (i % d->scaleMinor == 0)
        {
            painter->setPen(pen1);
            painter->drawLine(0, radius - 12, 0, radius);
        }
        else
        {
            painter->setPen(pen2);
            painter->drawLine(0, radius - 5, 0, radius);
        }
        painter->rotate(angle);
    }
    painter->restore();
}

void HArcGauge::drawScaleLabel(QPainter *painter)
{
    Q_D(HArcGauge);
    auto radius = 75;
    auto start = qDegreesToRadians(270.0 - d->angleStart);
    auto delta = qDegreesToRadians(angleSpan()) / d->scaleMajor;
    painter->save();
    painter->setPen(d->scaleLabelColor);
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

void HArcGauge::drawPointer(QPainter *painter)
{
    Q_D(HArcGauge);
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(d->pointerColor);
    painter->rotate(d->angleStart);
    painter->rotate(toAngle(d->currentValue));
    if (d->pointerStyle == Circle)
        drawPointerCircle(painter);
    if (d->pointerStyle == Indicator)
        drawPointerIndicator(painter);
    if (d->pointerStyle == IndicatorR)
        drawPointerIndicatorR(painter);
    if (d->pointerStyle == Triangle)
        drawPointerTriangle(painter);
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
    painter->setOpacity(0.8);
    painter->drawConvexPolygon(poly);
}

void HArcGauge::drawPointerIndicatorR(QPainter *painter)
{
    Q_D(HArcGauge);
    auto radius = 75;
    auto poly = QPolygon() << QPoint(-5, 0) << QPoint(5, 0) << QPoint(0, radius);
    painter->setPen(QPen(d->pointerColor, 1));
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

void HArcGauge::drawRoundCircle(QPainter *painter)
{
    Q_D(HArcGauge);
    auto radius = 12;
    painter->save();
    painter->setOpacity(0.5);
    painter->setPen(Qt::NoPen);
    painter->setBrush(d->pointerColor);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    painter->restore();
}
void HArcGauge::drawCenterCircle(QPainter *painter)
{
    Q_D(HArcGauge);
    auto radius = 8;
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(d->pointerColor);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    painter->restore();
}

void HArcGauge::drawValue(QPainter *painter)
{
    Q_D(HArcGauge);
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

double HArcGauge::angleSpan()
{
    Q_D(HArcGauge);
    return 360.0 - d->angleStart - d->angleEnd;
}

double HArcGauge::toAngle(double value)
{
    return angleSpan() * toRatio(value);
}

HE_CONTROL_END_NAMESPACE
