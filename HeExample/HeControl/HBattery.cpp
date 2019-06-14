#include "HBattery_p.h"
#include <QtCore/QPropertyAnimation>
#include <QtGui/QPainter>

HE_CONTROL_BEGIN_NAMESPACE

HBattery::HBattery(QWidget *parent) :
    QWidget(parent),
    d_ptr(new HBatteryPrivate)
{
    init();
}

HBattery::HBattery(HBatteryPrivate &p, QWidget *parent) :
    QWidget(parent),
    d_ptr(&p)
{
    init();
}

HBattery::~HBattery()
{
}

void HBattery::setRange(double minValue, double maxValue)
{
    if (minValue >= maxValue)
        qSwap(minValue, maxValue);

    d_ptr->minValue = minValue;
    d_ptr->maxValue = maxValue;
    if (d_ptr->value < minValue || d_ptr->value > maxValue)
        setValue(qBound(minValue, d_ptr->value, maxValue));
    else
        update();
}

void HBattery::setMinValue(double value)
{
    setRange(value, d_ptr->maxValue);
}

void HBattery::setMaxValue(double value)
{
    setRange(d_ptr->minValue, value);
}

void HBattery::setValue(double value)
{
    if (value < d_ptr->minValue || value >d_ptr-> maxValue)
        return;
    d_ptr->value = value;
    emit valueChanged(value);
    d_ptr->animation->stop();
    d_ptr->animation->setEndValue(value);
    d_ptr->animation->start();
}

void HBattery::setAlarmValue(double value)
{
    if (d_ptr->alarmValue == value)
        return;
    d_ptr->alarmValue = value;
    update();
}

void HBattery::setCurrentValue(double value)
{
    if (d_ptr->currentValue == value)
        return;
    d_ptr->currentValue = value;
    update();
}

void HBattery::setDuration(int value)
{
    if (d_ptr->animation->duration() == value)
        return;
    d_ptr->animation->setDuration(value);
}

void HBattery::setBorderColorStart(QColor value)
{
    if (d_ptr->borderColorStart == value)
        return;
    d_ptr->borderColorStart = value;
    update();
}

void HBattery::setBorderColorEnd(QColor value)
{
    if (d_ptr->borderColorEnd == value)
        return;
    d_ptr->borderColorEnd = value;
    update();
}

void HBattery::setAlarmColorStart(QColor value)
{
    if (d_ptr->alarmColorStart == value)
        return;
    d_ptr->alarmColorStart = value;
    update();
}

void HBattery::setAlarmColorEnd(QColor value)
{
    if (d_ptr->alarmColorEnd == value)
        return;
    d_ptr->alarmColorEnd = value;
    update();
}

void HBattery::setNormalColorStart(QColor value)
{
    if (d_ptr->normalColorStart == value)
        return;
    d_ptr->normalColorStart = value;
    update();
}

void HBattery::setNormalColorEnd(QColor value)
{
    if (d_ptr->normalColorEnd == value)
        return;
    d_ptr->normalColorEnd = value;
    update();
}

QSize HBattery::sizeHint() const
{
    return QSize(150, 80);
}

QSize HBattery::minimumSizeHint() const
{
    return QSize(30, 10);
}

double HBattery::minValue() const
{
    return d_ptr->minValue;
}

double HBattery::maxValue() const
{
    return d_ptr->maxValue;
}

double HBattery::value() const
{
    return d_ptr->value;
}

double HBattery::alarmValue() const
{
    return d_ptr->alarmValue;
}

double HBattery::currentValue() const
{
    return d_ptr->currentValue;
}

double HBattery::duration() const
{
    return d_ptr->animation->duration();
}

QColor HBattery::borderColorStart() const
{
    return d_ptr->borderColorStart;
}

QColor HBattery::borderColorEnd() const
{
    return d_ptr->borderColorEnd;
}

QColor HBattery::alarmColorStart() const
{
    return d_ptr->alarmColorStart;
}

QColor HBattery::alarmColorEnd() const
{
    return d_ptr->alarmColorEnd;
}

QColor HBattery::normalColorStart() const
{
    return d_ptr->normalColorStart;
}

QColor HBattery::normalColorEnd() const
{
    return d_ptr->normalColorEnd;
}

void HBattery::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    painter.save();
    // 绘制电池边框
    auto rect1 = QRectF(QPointF(5, 5), QPointF(width() * 9 / 10, height() - 5));
    painter.setPen(QPen(borderColorStart(), 5));
    painter.setBrush(Qt::NoBrush);
    painter.drawRoundRect(rect1, 10, 20);
    // 绘制电池头部
    auto rect2 = QRectF(QPointF(rect1.right(), height() / 3), QPointF(width() - 5, height() * 2 / 3));
    auto gradient2 = QLinearGradient(rect2.topLeft(), rect2.bottomLeft());
    gradient2.setColorAt(0.0, borderColorStart());
    gradient2.setColorAt(1.0, borderColorEnd());
    painter.setBrush(gradient2);
    painter.drawRoundRect(rect2, 15, 25);
    // 绘制电量
    auto margin = qMin(width(), height()) / 20;
    auto rect3 = rect1.adjusted(margin, margin, -margin, -margin);
    rect3.setWidth(rect3.width() * value() / 100);
    auto gradient3 = QLinearGradient(QPointF(0, 0), QPointF(0, height()));
    gradient3.setColorAt(0.0, value() <= alarmValue() ? alarmColorStart() : normalColorStart());
    gradient3.setColorAt(1.0, value() <= alarmValue() ? alarmColorEnd() : normalColorEnd());
    painter.setPen(Qt::NoPen);
    painter.setBrush(gradient3);
    painter.drawRoundRect(rect3, 10, 20);
    painter.restore();
}

void HBattery::init()
{
    d_ptr->animation = new QPropertyAnimation(this, "currentValue", this);
    d_ptr->animation->setEasingCurve(QEasingCurve::OutCubic);
    d_ptr->animation->setDuration(20000);
    d_ptr->animation->setStartValue(d_ptr->currentValue);
}

HE_CONTROL_END_NAMESPACE
