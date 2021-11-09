#include "HMiniGauge_p.h"
#include <QtCore/QtMath>
#include <QtGui/QPainter>
#include <QtGui/QMouseEvent>

HE_CONTROL_BEGIN_NAMESPACE

HMiniGaugePrivate::HMiniGaugePrivate()
{
    background = QColor(50, 50, 50);
    textColor = Qt::black;
}

HMiniGauge::HMiniGauge(QWidget *parent) :
    HCircleGauge(*new HMiniGaugePrivate, parent)
{
}

HMiniGauge::HMiniGauge(HMiniGaugePrivate &p, QWidget *parent) :
    HCircleGauge(p, parent)
{
}

HControlType::PointerStyle HMiniGauge::pointerStyle() const
{
    Q_D(const HMiniGauge);
    return d->pointerStyle;
}

QColor HMiniGauge::borderColor() const
{
    Q_D(const HMiniGauge);
    return d->borderColor;
}

QColor HMiniGauge::progressColor() const
{
    Q_D(const HMiniGauge);
    return d->progressColor;
}

bool HMiniGauge::doubleProgress() const
{
    Q_D(const HMiniGauge);
    return d->doubleProgress;
}

bool HMiniGauge::isShowValue() const
{
    Q_D(const HMiniGauge);
    return d->showValue;
}

void HMiniGauge::setPointerStyle(HControlType::PointerStyle value)
{
    Q_D(HMiniGauge);
    if (d->pointerStyle == value)
        return;
    d->pointerStyle = value;
    update();
}

void HMiniGauge::setBorderColor(const QColor &value)
{
    Q_D(HMiniGauge);
    if (d->borderColor == value)
        return;
    d->borderColor = value;
    update();
}

void HMiniGauge::setProgressColor(const QColor &value)
{
    Q_D(HMiniGauge);
    if (d->progressColor == value)
        return;
    d->progressColor = value;
    update();
}

void HMiniGauge::setDoubleProgress(bool b)
{
    Q_D(HMiniGauge);
    if (d->doubleProgress == b)
        return;
    d->doubleProgress = b;
    update();
}

void HMiniGauge::setShowValue(bool b)
{
    Q_D(HMiniGauge);
    if (d->showValue == b)
        return;
    d->showValue = b;
    update();
}

void HMiniGauge::mousePressEvent(QMouseEvent *e)
{
    Q_D(HMiniGauge);
    if (e->button() == Qt::LeftButton)
    {
        d->pressed = true;
        setPressedValue(e->localPos());
        return;
    }
    HCircleGauge::mousePressEvent(e);
}

void HMiniGauge::mouseReleaseEvent(QMouseEvent *e)
{
    Q_D(HMiniGauge);
    if (e->button() == Qt::LeftButton)
    {
        d->pressed = false;
        return;
    }
    HCircleGauge::mouseReleaseEvent(e);
}

void HMiniGauge::mouseMoveEvent(QMouseEvent *e)
{
    Q_D(HMiniGauge);
    if (d->pressed)
    {
        setPressedValue(e->localPos());
        return;
    }
    HCircleGauge::mouseMoveEvent(e);
}

void HMiniGauge::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    preDraw(&painter);
    drawProgress(&painter, 96);
    drawCircle(&painter);
    drawPointer(&painter, 100);
    drawValue(&painter, 100);
}

void HMiniGauge::drawProgress(QPainter *painter, int radius)
{
    Q_D(HMiniGauge);
    auto steps = d->scaleMajor * d->scaleMinor;
    if (steps == 0)
        return;

    auto angle = angleSpan() / steps;
    auto current = static_cast<int>(toAngle(d->currentValue));
    auto pen = QPen(d->scaleColor, 5.0, Qt::SolidLine, Qt::RoundCap);
    auto rotate = 0.0;
    QColor color;

    painter->save();
    painter->rotate(d->angleStart);
    for (int i = 0; i <= steps; i++)
    {
        rotate = angle * i;
        if (d->doubleProgress)
        {
            auto right = i >= (steps / 2);
            if (!right)
                color = (rotate < current) ? d->scaleColor : d->progressColor;
            else
                color = (rotate <= current) ? d->progressColor : d->scaleColor;
            // 矫正左侧值为最小值时第一格颜色
            if (qFuzzyCompare(d->currentValue, d->minimum) && !right)
                color = d->progressColor;
            // 矫正左侧值时中间格颜色
            if (d->currentValue <= (range() / 2 + d->minimum) && i == (steps / 2))
                color = d->progressColor;
            // 矫正中间值中间格颜色
            if (qFuzzyCompare(d->currentValue, (range() / 2 + d->minimum)))
                color = d->scaleColor;
        }
        else
        {
            color = (rotate <= current) ? d->scaleColor : d->progressColor;
            // 矫正左侧值为最小值时第一格颜色
            if (qFuzzyCompare(d->currentValue, d->minimum))
                color = d->scaleColor;
        }

        pen.setColor(color);
        painter->setPen(pen);
        if (i % d->scaleMinor == 0)
            painter->drawLine(0, radius, 0, radius - 10);
        else
            painter->drawLine(0, radius, 0, radius - 5);
        painter->rotate(angle);
    }
    painter->restore();
}

void HMiniGauge::drawPointer(QPainter *painter, int /*radius*/)
{
    Q_D(HMiniGauge);
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

void HMiniGauge::drawValue(QPainter *painter, int /*radius*/)
{
    Q_D(HMiniGauge);
    if (!isShowValue())
        return;

    auto f = font();
    f.setPixelSize(25);
    auto rect = QRectF(-50, 65, 100, 35);
    auto text = QString::number(d->currentValue, 'f', d->decimal);
    painter->save();
    painter->setPen(d->textColor);
    painter->setFont(f);
    painter->drawText(rect, Qt::AlignBottom | Qt::AlignHCenter, text);
    painter->restore();
}

void HMiniGauge::drawPointerCircle(QPainter *painter)
{
    auto radius = 8;
    auto offset = 30;
    painter->drawEllipse(-radius, radius + offset, radius * 2, radius * 2);
}

void HMiniGauge::drawPointerIndicator(QPainter *painter)
{
    auto radius = 70;
    auto poly = QPolygon() << QPoint(-5, 0) << QPoint(5, 0) << QPoint(0, radius);
    painter->drawConvexPolygon(poly);
}

void HMiniGauge::drawPointerIndicatorR(QPainter *painter)
{
    auto radius = 70;
    auto poly = QPolygon() << QPoint(-5, 0) << QPoint(5, 0) << QPoint(0, radius);
    painter->setPen(QPen(pointerColor(), 1));
    painter->setOpacity(1.0);
    painter->drawConvexPolygon(poly);
    // 增加绘制圆角直线,与之前三角形重叠,形成圆角指针
    painter->setPen(QPen(pointerColor(), 4, Qt::SolidLine, Qt::RoundCap));
    painter->drawLine(0, 0, 0, radius);
}

void HMiniGauge::drawPointerTriangle(QPainter *painter)
{
    auto radius = 10;
    auto offset = 55;
    auto poly = QPolygon() << QPoint(-5, offset) << QPoint(5, offset) << QPoint(0, radius + offset);
    painter->drawConvexPolygon(poly);
}

void HMiniGauge::drawPointerCenter(QPainter *painter)
{
    auto radius = 12;
    painter->setOpacity(0.5);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    radius -= 4;
    painter->setOpacity(1.0);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
}

void HMiniGauge::drawCircle(QPainter *painter)
{
    Q_D(HMiniGauge);
    auto radius = 75;
    painter->save();
    painter->setPen(QPen(d->borderColor, 5));
    painter->setBrush(d->background);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    painter->restore();
}

void HMiniGauge::setPressedValue(QPointF value)
{
    auto p = value - rect().center();
    auto r = atan2(-p.x(), p.y());
    auto a = qRadiansToDegrees(r);
    if (a < 0)
        a += 360;
    auto v = fromAngle(a);
    setValue(v);
}

HE_CONTROL_END_NAMESPACE
