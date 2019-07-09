#include "HKnobGauge_p.h"
#include <QtCore/QPropertyAnimation>
#include <QtGui/QPainter>
#include <QtGui/QMouseEvent>
#include <QtCore/QtMath>

HE_CONTROL_BEGIN_NAMESPACE

HKnobGauge::HKnobGauge(QWidget *parent) :
    HAnimationProgress(*new HKnobGaugePrivate, parent)
{
    init();
}

HKnobGauge::HKnobGauge(HKnobGaugePrivate &p, QWidget *parent) :
    HAnimationProgress(p, parent)
{
    init();
}

HKnobGauge::~HKnobGauge()
{
}

QSize HKnobGauge::sizeHint() const
{
    return QSize(200, 200);
}

QSize HKnobGauge::minimumSizeHint() const
{
    return QSize(20, 20);
}

int HKnobGauge::angleStart() const
{
    Q_D(const HKnobGauge);
    return d->angleStart;
}

int HKnobGauge::angleEnd() const
{
    Q_D(const HKnobGauge);
    return d->angleEnd;
}

QColor HKnobGauge::background() const
{
    Q_D(const HKnobGauge);
    return d->background;
}

QColor HKnobGauge::progressBackground() const
{
    Q_D(const HKnobGauge);
    return d->progressBackground;
}

QColor HKnobGauge::progressColor() const
{
    Q_D(const HKnobGauge);
    return d->progressColor;
}

QColor HKnobGauge::circleColorStart() const
{
    Q_D(const HKnobGauge);
    return d->circleColorStart;
}

QColor HKnobGauge::circleColorEnd() const
{
    Q_D(const HKnobGauge);
    return d->circleColorEnd;
}

QColor HKnobGauge::textColor() const
{
    Q_D(const HKnobGauge);
    return d->textColor;
}

bool HKnobGauge::isShowPointer() const
{
    Q_D(const HKnobGauge);
    return d->showPointer;
}

bool HKnobGauge::isShowValue() const
{
    Q_D(const HKnobGauge);
    return d->showValue;
}

HKnobGauge::PointerStyle HKnobGauge::pointerStyle() const
{
    Q_D(const HKnobGauge);
    return d->pointerStyle;
}

void HKnobGauge::setAngleStart(int value)
{
    Q_D(HKnobGauge);
    if (d->angleStart == value)
        return;
    d->angleStart = value;
    update();
}

void HKnobGauge::setAngleEnd(int value)
{
    Q_D(HKnobGauge);
    if (d->angleEnd == value)
        return;
    d->angleEnd = value;
    update();
}

void HKnobGauge::setBackground(const QColor &value)
{
    Q_D(HKnobGauge);
    if (d->background == value)
        return;
    d->background = value;
    update();
}

void HKnobGauge::setProgressBackground(const QColor &value)
{
    Q_D(HKnobGauge);
    if (d->progressBackground == value)
        return;
    d->progressBackground = value;
    update();
}

void HKnobGauge::setProgressColor(const QColor &value)
{
    Q_D(HKnobGauge);
    if (d->progressColor == value)
        return;
    d->progressColor = value;
    update();
}

void HKnobGauge::setCircleColorStart(const QColor &value)
{
    Q_D(HKnobGauge);
    if (d->circleColorStart == value)
        return;
    d->circleColorStart = value;
    update();
}

void HKnobGauge::setCircleColorEnd(const QColor &value)
{
    Q_D(HKnobGauge);
    if (d->circleColorEnd == value)
        return;
    d->circleColorEnd = value;
    update();
}

void HKnobGauge::setTextColor(const QColor &value)
{
    Q_D(HKnobGauge);
    if (d->textColor == value)
        return;
    d->textColor = value;
    update();
}

void HKnobGauge::setShowPointer(bool b)
{
    Q_D(HKnobGauge);
    if (d->showPointer == b)
        return;
    d->showPointer = b;
    update();
}

void HKnobGauge::setShowValue(bool b)
{
    Q_D(HKnobGauge);
    if (d->showValue == b)
        return;
    d->showValue = b;
    update();
}

void HKnobGauge::setPointerStyle(PointerStyle value)
{
    Q_D(HKnobGauge);
    if (d->pointerStyle == value)
        return;
    d->pointerStyle = value;
    update();
}

void HKnobGauge::enterEvent(QEvent *)
{
    Q_D(HKnobGauge);
    if (d->hover)
        return;
    d->hover = true;
    d->animationHover->setStartValue(d->radiusCoverCircle);
    d->animationHover->setEndValue(75);
    d->animationHover->start();
}

void HKnobGauge::leaveEvent(QEvent *)
{
    Q_D(HKnobGauge);
    if (!d->hover)
        return;
    d->hover = false;
    d->animationHover->setStartValue(d->radiusCoverCircle);
    d->animationHover->setEndValue(85);
    d->animationHover->start();
}

void HKnobGauge::mousePressEvent(QMouseEvent *e)
{
    Q_D(HKnobGauge);
    if (e->button() == Qt::LeftButton)
    {
        d->pressed = true;
        setPressedValue(e->localPos());
        return;
    }
    HAnimationProgress::mousePressEvent(e);
}

void HKnobGauge::mouseReleaseEvent(QMouseEvent *e)
{
    Q_D(HKnobGauge);
    if (e->button() == Qt::LeftButton)
    {
        d->pressed = false;
        return;
    }
    HAnimationProgress::mouseReleaseEvent(e);
}

void HKnobGauge::mouseMoveEvent(QMouseEvent *e)
{
    Q_D(HKnobGauge);
    if (d->pressed)
    {
        setPressedValue(e->localPos());
        return;
    }
    HAnimationProgress::mouseMoveEvent(e);
}

void HKnobGauge::paintEvent(QPaintEvent *)
{
    auto side = qMin(width(), height());
    QPainter painter(this);
    // 绘制准备工作,启用反锯齿,平移坐标轴中心,等比例缩放
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    painter.translate(width() / 2, height() / 2);
    painter.scale(side / 200.0, side / 200.0);
    // 绘制背景
    drawBackground(&painter);
    // 绘制饼圆
    drawColorPie(&painter);
    // 绘制覆盖圆 用以遮住饼圆多余部分
    drawCoverCircle(&painter);
    // 绘制中心圆
    drawCircle(&painter);
    // 绘制指示器
    drawPointer(&painter);
    // 绘制当前值
    drawValue(&painter);
}

void HKnobGauge::drawBackground(QPainter *painter)
{
    Q_D(HKnobGauge);
    auto radius = 99;
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(d->background);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    painter->restore();
}

void HKnobGauge::drawColorPie(QPainter *painter)
{
    Q_D(HKnobGauge);
    auto radius = 95;
    auto rect = QRectF(-radius, -radius, radius * 2, radius * 2);
    auto current = static_cast<int>(toAngle(d->currentValue));
    auto other = static_cast<int>(toAngle(d->maximum - d->currentValue));

    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(d->progressColor);
    painter->drawPie(rect, (270 - d->angleStart - current) * 16, current * 16);
    painter->setBrush(d->progressBackground);
    painter->drawPie(rect, (270 - d->angleStart - current - other) * 16, other * 16);
    painter->restore();
}

void HKnobGauge::drawCoverCircle(QPainter *painter)
{
    Q_D(HKnobGauge);
    auto radius = d->radiusCoverCircle;
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(d->background);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    painter->restore();
}

void HKnobGauge::drawCircle(QPainter *painter)
{
    Q_D(HKnobGauge);
    auto radius = d->radiusCircle;
    auto gradient = QLinearGradient(0, -radius, 0, radius);
    gradient.setColorAt(0.0, d->circleColorStart);
    gradient.setColorAt(1.0, d->circleColorEnd);
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(gradient);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    painter->restore();
}

void HKnobGauge::drawPointer(QPainter *painter)
{
    Q_D(HKnobGauge);
    if (!d->showPointer)
        return;
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(d->progressColor);
    painter->rotate(d->angleStart);
    painter->rotate(toAngle(d->currentValue));
    if (d->pointerStyle == PointerStyle_Circle)
        drawPointerCircle(painter);
    if (d->pointerStyle == PointerStyle_Indicator)
        drawPointerIndicator(painter);
    if (d->pointerStyle == PointerStyle_IndicatorR)
        drawPointerIndicatorR(painter);
    if (d->pointerStyle == PointerStyle_Triangle)
        drawPointerTriangle(painter);
    painter->restore();
}

void HKnobGauge::drawPointerCircle(QPainter *painter)
{
    Q_D(HKnobGauge);
    auto radius = 15;
    auto offset = d->radiusCircle - 60;
    painter->drawEllipse(-radius, radius + offset, radius * 2, radius * 2);
}

void HKnobGauge::drawPointerIndicator(QPainter *painter)
{
    Q_D(HKnobGauge);
    auto radius = d->radiusCircle - 15;
    auto poly = QPolygon() << QPoint(-8, 0) << QPoint(8, 0) << QPoint(0, radius);
    painter->drawConvexPolygon(poly);
    // 绘制中心圆点
    radius = radius / 4;
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
}

void HKnobGauge::drawPointerIndicatorR(QPainter *painter)
{
    Q_D(HKnobGauge);
    auto radius = d->radiusCircle - 15;
    auto poly = QPolygon() << QPoint(-8, 0) << QPoint(8, 0) << QPoint(0, radius);
    painter->setPen(QPen(d->progressColor, 1));
    painter->drawConvexPolygon(poly);
    // 增加绘制圆角直线,与之前三角形重叠,形成圆角指针
    painter->setPen(QPen(d->progressColor, 4, Qt::SolidLine, Qt::RoundCap));
    painter->drawLine(0, 0, 0, radius);
    // 绘制中心圆点
    radius = radius / 4;
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
}

void HKnobGauge::drawPointerTriangle(QPainter *painter)
{
    Q_D(HKnobGauge);
    auto radius = 20;
    auto offset = d->radiusCircle - 25;
    auto poly = QPolygon() << QPoint(-radius / 2, offset) << QPoint(radius / 2, offset) << QPoint(0, radius + offset);
    painter->drawConvexPolygon(poly);
}

void HKnobGauge::drawValue(QPainter *painter)
{
    Q_D(HKnobGauge);
    if (!d->showValue)
        return;
    auto radius = 100;
    auto rect = QRectF(-radius, radius / 2, radius * 2, radius / 3);
    auto text = QString::number(d->currentValue, 'f', d->decimal);
    auto f = font();
    f.setPixelSize(d->showPointer ? radius - 50 : radius - 15);
    f.setBold(true);

    painter->save();
    painter->setPen(d->textColor);
    painter->setFont(f);
    painter->drawText(rect, Qt::AlignCenter, text);
    painter->restore();
}

double HKnobGauge::angleSpan()
{
    Q_D(HKnobGauge);
    return 360.0 - d->angleStart - d->angleEnd;
}

double HKnobGauge::toAngle(double value)
{
    return angleSpan() * toRatio(value);
}

double HKnobGauge::fromAngle(double value)
{
    Q_D(HKnobGauge);
    value = qBound(d->angleStart * 1.0, value, 360.0 - d->angleEnd);
    return fromRatio((value - d->angleStart) / angleSpan());
}

void HKnobGauge::init()
{
    Q_D(HKnobGauge);
    d->animationHover = new QPropertyAnimation(this);
    d->animationHover->setTargetObject(this);
    d->animationHover->setEasingCurve(QEasingCurve::Linear);
    connect(d->animationHover, &QPropertyAnimation::valueChanged, this, &HKnobGauge::updateRadius);
}

void HKnobGauge::updateRadius(QVariant value)
{
    Q_D(HKnobGauge);
    d->radiusCoverCircle = value.toInt();
    d->radiusCircle = d->radiusCoverCircle - 5;
    update();
}

void HKnobGauge::setPressedValue(QPointF value)
{
    auto p = value - rect().center();
    auto r = qAtan2(-p.x(), p.y());
    auto a = qRadiansToDegrees(r);
    if (a < 0)
        a += 360;
    auto v = fromAngle(a);
    setValue(v);
}

HE_CONTROL_END_NAMESPACE
