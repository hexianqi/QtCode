#include "HClockGauge_p.h"
#include <QtCore/QPropertyAnimation>
#include <QtCore/QtMath>
#include <QtCore/QTime>
#include <QtCore/QTimer>
#include <QtGui/QPainter>

HE_BEGIN_NAMESPACE

HClockGauge::HClockGauge(QWidget *parent) :
    QWidget(parent),
    d_ptr(new HClockGaugePrivate)
{
    init();
}

HClockGauge::HClockGauge(HClockGaugePrivate &p, QWidget *parent) :
    QWidget(parent),
    d_ptr(&p)
{
    init();
}

HClockGauge::~HClockGauge()
{
    d_ptr->timer->stop();
}

QSize HClockGauge::sizeHint() const
{
    return {200, 200};
}

QSize HClockGauge::minimumSizeHint() const
{
    return {20, 20};
}

QColor HClockGauge::foreground() const
{
    return d_ptr->foreground;
}

QColor HClockGauge::background() const
{
    return d_ptr->background;
}

QColor HClockGauge::crownColorStart() const
{
    return d_ptr->crownColorStart;
}

QColor HClockGauge::crownColorEnd() const
{
    return d_ptr->crownColorEnd;
}

QColor HClockGauge::pointerHourColor() const
{
    return d_ptr->pointerHourColor;
}

QColor HClockGauge::pointerMinColor() const
{
    return d_ptr->pointerMinColor;
}

QColor HClockGauge::pointerSecColor() const
{
    return d_ptr->pointerSecColor;
}

HClockGauge::SecondStyle HClockGauge::secondStyle() const
{
    return d_ptr->secondStyle;
}

void HClockGauge::setForeground(const QColor &value)
{
    if (d_ptr->foreground == value)
        return;
    d_ptr->foreground = value;
    update();
}

void HClockGauge::setBackground(const QColor &value)
{
    if (d_ptr->background == value)
        return;
    d_ptr->background = value;
    update();
}

void HClockGauge::setCrownColorStart(const QColor &value)
{
    if (d_ptr->crownColorStart == value)
        return;
    d_ptr->crownColorStart = value;
    update();
}

void HClockGauge::setCrownColorEnd(const QColor &value)
{
    if (d_ptr->crownColorEnd == value)
        return;
    d_ptr->crownColorEnd = value;
    update();
}

void HClockGauge::setPointerHourColor(const QColor &value)
{
    if (d_ptr->pointerHourColor == value)
        return;
    d_ptr->pointerHourColor = value;
    update();
}

void HClockGauge::setPointerMinColor(const QColor &value)
{
    if (d_ptr->pointerMinColor == value)
        return;
    d_ptr->pointerMinColor = value;
    update();
}

void HClockGauge::setPointerSecColor(const QColor &value)
{
    if (d_ptr->pointerSecColor == value)
        return;
    d_ptr->pointerSecColor = value;
    update();
}

void HClockGauge::setSecondStyle(HClockGauge::SecondStyle value)
{
    if (d_ptr->secondStyle == value)
        return;
    d_ptr->secondStyle = value;

    if (value == SecondStyle_Spring)
        d_ptr->animation->setEasingCurve(QEasingCurve::OutElastic);
    if (value == SecondStyle_Continue)
        d_ptr->animation->setEasingCurve(QEasingCurve::Linear);
    update();
}

void HClockGauge::paintEvent(QPaintEvent *)
{
    auto side = qMin(width(), height());
    QPainter painter(this);
    // 绘制准备工作,启用反锯齿,平移坐标轴中心,等比例缩放
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    painter.translate(width() / 2.0, height() / 2.0);
    painter.scale(side / 200.0, side / 200.0);

    // 绘制外边框
    drawCrown(&painter);
    // 绘制背景
    drawBackground(&painter);
    // 绘制刻度线
    drawScale(&painter);
    // 绘制刻度值
    drawScaleLabel(&painter);
    // 绘制时钟指针
    drawHour(&painter);
    // 绘制分钟指针
    drawMin(&painter);
    // 绘制秒钟指针
    drawSec(&painter);
    // 绘制中心盖板
    drawDot(&painter);
}

void HClockGauge::drawCrown(QPainter *painter)
{
    auto radius = 99;
    painter->save();
    painter->setPen(Qt::NoPen);
    auto gradient = QLinearGradient(0, -radius, 0, radius);
    gradient.setColorAt(0, d_ptr->crownColorStart);
    gradient.setColorAt(1, d_ptr->crownColorEnd);
    painter->setBrush(gradient);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    painter->restore();
}

void HClockGauge::drawBackground(QPainter *painter)
{
    auto radius = 92;
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(d_ptr->background);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    painter->restore();
}

void HClockGauge::drawScale(QPainter *painter)
{
    auto radius = 90;
    auto pen = QPen(d_ptr->foreground, 1, Qt::SolidLine, Qt::RoundCap);
    painter->save();

    for (int i = 0; i <= 60; i++)
    {
        if (i % 5 == 0)
        {
            pen.setWidthF(1.5);
            painter->setPen(pen);
            painter->drawLine(0, radius - 10, 0, radius);
        }
        else
        {
            pen.setWidthF(0.5);
            painter->setPen(pen);
            painter->drawLine(0, radius - 5, 0, radius);
        }
        painter->rotate(6);
    }
    painter->restore();
}

void HClockGauge::drawScaleLabel(QPainter *painter)
{
    auto radius = 70;
    auto start = qDegreesToRadians(60.0);
    auto delta = qDegreesToRadians(30.0);
    painter->save();
    painter->setPen(d_ptr->foreground);
    for (int i = 0; i < 12; i++)
    {
        auto angle = start - i * delta;
        auto text = QString("%1").arg(i + 1);
        auto textWidth = fontMetrics().width(text);
        auto textHeight = fontMetrics().height();
        auto x = radius * cos(angle) - textWidth / 2.0;
        auto y = -radius * sin(angle) + textHeight / 4.0;
        painter->drawText(QPointF(x, y), text);
    }
    painter->restore();
}

void HClockGauge::drawHour(QPainter *painter)
{
    auto poly = QPolygon() << QPoint(-3, 8) << QPoint(3, 8) << QPoint(2, -40) << QPoint(-2, -40);
    painter->save();
    painter->setPen(QPen(d_ptr->pointerHourColor, 1, Qt::SolidLine, Qt::RoundCap));
    painter->setBrush(d_ptr->pointerHourColor);
    painter->rotate(30.0 * (d_ptr->hour + d_ptr->min / 60.0));
    painter->drawConvexPolygon(poly);
    painter->restore();
}

void HClockGauge::drawMin(QPainter *painter)
{
    auto poly = QPolygon() << QPoint(-2, 8) << QPoint(2, 8) << QPoint(1, -60) << QPoint(-1, -60);
    painter->save();
    painter->setPen(QPen(d_ptr->pointerMinColor, 1, Qt::SolidLine, Qt::RoundCap));
    painter->setBrush(d_ptr->pointerMinColor);
    painter->rotate(6.0 * (d_ptr->min + d_ptr->sec / 60.0));
    painter->drawConvexPolygon(poly);
    painter->restore();
}

void HClockGauge::drawSec(QPainter *painter)
{
    if (d_ptr->secondStyle == SecondStyle_Hide)
        return;

    auto poly = QPolygon() << QPoint(-1, 10) << QPoint(1, 10) << QPoint(0, -70);
    painter->save();
    painter->setPen(QPen(d_ptr->pointerSecColor, 1, Qt::SolidLine, Qt::RoundCap));
    painter->setBrush(d_ptr->pointerSecColor);
    painter->rotate(d_ptr->angleSpring);
    painter->drawConvexPolygon(poly);
    painter->restore();
}

void HClockGauge::drawDot(QPainter *painter)
{
    auto gradient = QConicalGradient(0, 0, -90.0);
    gradient.setColorAt(0.0, d_ptr->background);
    gradient.setColorAt(0.5, d_ptr->foreground);
    gradient.setColorAt(1.0, d_ptr->background);
    painter->save();
    painter->setOpacity(0.9);
    painter->setPen(Qt::NoPen);
    painter->setBrush(gradient);
    painter->drawEllipse(-5, -5, 10, 10);
    painter->restore();
}

void HClockGauge::init()
{
    d_ptr->timer = new QTimer(this);
    d_ptr->timer->setInterval(1000);
    d_ptr->animation = new QPropertyAnimation(this);
    d_ptr->animation->setDuration(1000);
    d_ptr->animation->setTargetObject(this);
    d_ptr->animation->setEasingCurve(QEasingCurve::Linear);
    connect(d_ptr->timer, &QTimer::timeout, this, &HClockGauge::updateTime);
    connect(d_ptr->animation, &QPropertyAnimation::valueChanged, this, &HClockGauge::updateSpring);
    setSecondStyle(SecondStyle_Spring);
    d_ptr->timer->start();
}

void HClockGauge::updateTime()
{
    auto time = QTime::currentTime();
    d_ptr->hour = time.hour();
    d_ptr->min = time.minute();
    d_ptr->sec = time.second();
    d_ptr->animation->stop();
    if (d_ptr->secondStyle == SecondStyle_Spring || d_ptr->secondStyle == SecondStyle_Continue)
    {
        d_ptr->animation->setStartValue(-1.0);
        d_ptr->animation->setEndValue(0.0);
        d_ptr->animation->start();
    }
    else
    {
        d_ptr->angleSpring = 6.0 * d_ptr->sec;
        update();
    }
}

void HClockGauge::updateSpring(const QVariant &value)
{
    d_ptr->angleSpring = 6.0 * (d_ptr->sec + value.toDouble());
    update();
}

HE_END_NAMESPACE
