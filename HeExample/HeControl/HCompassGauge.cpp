#include "HCompassGauge_p.h"
#include <QtCore/QPropertyAnimation>
#include <QtGui/QPainter>

HE_CONTROL_BEGIN_NAMESPACE

HCompassGauge::HCompassGauge(QWidget *parent) :
    QWidget(parent),
    d_ptr(new HCompassGaugePrivate)
{
    init();
}

HCompassGauge::HCompassGauge(HCompassGaugePrivate &p, QWidget *parent) :
    QWidget(parent),
    d_ptr(&p)
{
    init();
}

HCompassGauge::~HCompassGauge() = default;

QSize HCompassGauge::sizeHint() const
{
    return {200, 200};
}

QSize HCompassGauge::minimumSizeHint() const
{
    return {40, 40};
}

double HCompassGauge::value() const
{
    return d_ptr->value;
}

int HCompassGauge::decimal() const
{
    return d_ptr->decimal;
}

QColor HCompassGauge::foreground() const
{
    return d_ptr->foreground;
}

QColor HCompassGauge::backgroundStart() const
{
    return d_ptr->backgroundStart;
}

QColor HCompassGauge::backgroundEnd() const
{
    return d_ptr->backgroundEnd;
}

QColor HCompassGauge::textColor() const
{
    return d_ptr->textColor;
}

QColor HCompassGauge::darkColor() const
{
    return d_ptr->darkColor;
}

QColor HCompassGauge::lightColor() const
{
    return d_ptr->lightColor;
}

QColor HCompassGauge::northPointerColor() const
{
    return d_ptr->northPointerColor;
}

QColor HCompassGauge::southPointerColor() const
{
    return d_ptr->southPointerColor;
}

QColor HCompassGauge::crownColorStart() const
{
    return d_ptr->crownColorStart;
}

QColor HCompassGauge::crownColorEnd() const
{
    return d_ptr->crownColorEnd;
}

QColor HCompassGauge::centerColorStart() const
{
    return d_ptr->centerColorStart;
}

QColor HCompassGauge::centerColorEnd() const
{
    return d_ptr->centerColorEnd;
}

void HCompassGauge::setValue(double value)
{
    if (qFuzzyCompare(d_ptr->value, value) || value < 0 || value > 360)
        return;
    d_ptr->value = value;
    emit valueChanged(value);
    d_ptr->animation->setStartValue(d_ptr->currentValue);
    d_ptr->animation->setEndValue(value);
    d_ptr->animation->start();
}

void HCompassGauge::setDecimal(int value)
{
    if (d_ptr->decimal == value)
        return;
    d_ptr->decimal = value;
    update();
}

void HCompassGauge::setForeground(const QColor &value)
{
    if (d_ptr->foreground == value)
        return;
    d_ptr->foreground = value;
    update();
}

void HCompassGauge::setBackgroundStart(const QColor &value)
{
    if (d_ptr->backgroundStart == value)
        return;
    d_ptr->backgroundStart = value;
    update();
}

void HCompassGauge::setBackgroundEnd(const QColor &value)
{
    if (d_ptr->backgroundEnd == value)
        return;
    d_ptr->backgroundEnd = value;
    update();
}

void HCompassGauge::setTextColor(const QColor &value)
{
    if (d_ptr->textColor == value)
        return;
    d_ptr->textColor = value;
    update();
}

void HCompassGauge::setDarkColor(const QColor &value)
{
    if (d_ptr->darkColor == value)
        return;
    d_ptr->darkColor = value;
    update();
}

void HCompassGauge::setLightColor(const QColor &value)
{
    if (d_ptr->lightColor == value)
        return;
    d_ptr->lightColor = value;
    update();
}

void HCompassGauge::setNorthPointerColor(const QColor &value)
{
    if (d_ptr->northPointerColor == value)
        return;
    d_ptr->northPointerColor = value;
    update();
}

void HCompassGauge::setSouthPointerColor(const QColor &value)
{
    if (d_ptr->southPointerColor == value)
        return;
    d_ptr->southPointerColor = value;
    update();
}

void HCompassGauge::setCrownColorStart(const QColor &value)
{
    if (d_ptr->crownColorStart == value)
        return;
    d_ptr->crownColorStart = value;
    update();
}

void HCompassGauge::setCrownColorEnd(const QColor &value)
{
    if (d_ptr->crownColorEnd == value)
        return;
    d_ptr->crownColorEnd = value;
    update();
}

void HCompassGauge::setCenterColorStart(const QColor &value)
{
    if (d_ptr->centerColorStart == value)
        return;
    d_ptr->centerColorStart = value;
    update();
}

void HCompassGauge::setCenterColorEnd(const QColor &value)
{
    if (d_ptr->centerColorEnd == value)
        return;
    d_ptr->centerColorEnd = value;
    update();
}

void HCompassGauge::setCurrentValue(double value)
{
    if (qFuzzyCompare(d_ptr->currentValue, value))
        return;
    d_ptr->currentValue = value;
    update();
}

void HCompassGauge::paintEvent(QPaintEvent *)
{
    auto side = qMin(width(), height());
    QPainter painter(this);
    // 绘制准备工作,启用反锯齿,平移坐标轴中心,等比例缩放
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    painter.translate(width() / 2.0, height() / 2.0);
    painter.scale(side / 200.0, side / 200.0);
    // 绘制外边框圆
    drawCrownCircle(&painter);
    // 绘制背景圆
    drawBackground(&painter);
    // 绘制刻度
    drawScale(&painter);
    // 绘制东南西北标识
    drawScaleLabel(&painter);
    // 绘制覆盖圆外圆
    drawCoverOuterCircle(&painter);
    // 绘制覆盖圆内圆
    drawCoverInnerCircle(&painter);
    // 绘制覆盖圆中心圆
    drawCoverCenterCircle(&painter);
    // 绘制南北指针
    drawPointer(&painter);
    // 绘制中心圆
    drawCenterCircle(&painter);
    // 绘制当前值
    drawValue(&painter);
}

void HCompassGauge::drawCrownCircle(QPainter *painter)
{
    auto radius = 99;
    auto gradient = QLinearGradient(0, -radius, 0, radius);
    gradient.setColorAt(0, d_ptr->crownColorStart);
    gradient.setColorAt(1, d_ptr->crownColorEnd);
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(gradient);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    painter->restore();
}

void HCompassGauge::drawBackground(QPainter *painter)
{
    auto radius = 90;
    auto gradient = QLinearGradient(0, -radius, 0, radius);
    gradient.setColorAt(0, d_ptr->backgroundStart);
    gradient.setColorAt(1, d_ptr->backgroundEnd);
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(gradient);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    painter->restore();
}

void HCompassGauge::drawScale(QPainter *painter)
{
    auto radius = 85;
    auto steps = 8;
    auto angle = 360.0 / steps;
    painter->save();
    painter->setPen(QPen(d_ptr->foreground, 4, Qt::SolidLine, Qt::RoundCap));
    for (int i = 0; i <= steps; i++)
    {
        if (i % 2 != 0)
            painter->drawLine(0, radius - 10, 0, radius);
        painter->rotate(angle);
    }
    painter->restore();
}

void HCompassGauge::drawScaleLabel(QPainter *painter)
{
    auto radius = 88;
    auto f = font();
    f.setPixelSize(15);
    f.setBold(true);

    painter->save();
    painter->setPen(d_ptr->foreground);
    painter->setFont(f);
    auto rect = QRect(-radius, -radius, radius * 2, radius * 2);
    painter->drawText(rect, Qt::AlignTop | Qt::AlignHCenter, "N");
    painter->drawText(rect, Qt::AlignBottom | Qt::AlignHCenter, "S");
    radius -= 2;
    rect = QRect(-radius, -radius, radius * 2, radius * 2);
    painter->drawText(rect, Qt::AlignLeft | Qt::AlignVCenter, "W");
    radius -= 2;
    rect = QRect(-radius, -radius, radius * 2, radius * 2);
    painter->drawText(rect, Qt::AlignRight | Qt::AlignVCenter, "E");
    painter->restore();
}

void HCompassGauge::drawCoverOuterCircle(QPainter *painter)
{
    auto radius = 68;
    auto gradient = QLinearGradient(0, -radius, 0, radius);
    gradient.setColorAt(0, d_ptr->lightColor);
    gradient.setColorAt(1, d_ptr->darkColor);
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(gradient);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    painter->restore();
}

void HCompassGauge::drawCoverInnerCircle(QPainter *painter)
{
    auto radius = 60;
    auto gradient = QLinearGradient(0, -radius, 0, radius);
    gradient.setColorAt(0, d_ptr->darkColor);
    gradient.setColorAt(1, d_ptr->lightColor);
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(gradient);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    painter->restore();
}

void HCompassGauge::drawCoverCenterCircle(QPainter *painter)
{
    auto radius = 15;
    auto gradient = QLinearGradient(0, -radius, 0, radius);
    gradient.setColorAt(0, d_ptr->lightColor);
    gradient.setColorAt(1, d_ptr->darkColor);
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setOpacity(0.8);
    painter->setBrush(gradient);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    painter->restore();
}

void HCompassGauge::drawPointer(QPainter *painter)
{
    auto radius = 75;
    auto pts = QPolygon() << QPoint(-10, 0) << QPoint(10, 0) << QPoint(0, radius);
    painter->save();
    painter->setOpacity(0.7);
    painter->setPen(Qt::NoPen);
    painter->setBrush(d_ptr->southPointerColor);
    painter->rotate(d_ptr->currentValue);
    painter->drawConvexPolygon(pts);
    painter->setBrush(d_ptr->northPointerColor);
    painter->rotate(180);
    painter->drawConvexPolygon(pts);
    painter->restore();
}

void HCompassGauge::drawCenterCircle(QPainter *painter)
{
    auto radius = 12;
    auto gradient = QLinearGradient(0, -radius, 0, radius);
    gradient.setColorAt(0, d_ptr->centerColorStart);
    gradient.setColorAt(1, d_ptr->centerColorEnd);
    painter->save();
    painter->setOpacity(1.0);
    painter->setPen(Qt::NoPen);
    painter->setBrush(gradient);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    painter->restore();
}

void HCompassGauge::drawValue(QPainter *painter)
{
    int radius = 100;
    auto rect = QRectF(-radius, -radius, radius * 2, radius * 2);
    auto text = QString::number(d_ptr->currentValue, 'f', d_ptr->decimal);
    auto f = font();
    f.setPixelSize(11);
    f.setBold(true);
    painter->save();
    painter->setPen(d_ptr->textColor);
    painter->setFont(f);
    painter->drawText(rect, Qt::AlignCenter, text);
    painter->restore();
}

void HCompassGauge::init()
{
    d_ptr->animation = new QPropertyAnimation(this);
    d_ptr->animation->setTargetObject(this);
    d_ptr->animation->setEasingCurve(QEasingCurve::Linear);
    connect(d_ptr->animation, &QPropertyAnimation::valueChanged, this, [=](QVariant value) { setCurrentValue(value.toDouble()); });
}

HE_CONTROL_END_NAMESPACE
