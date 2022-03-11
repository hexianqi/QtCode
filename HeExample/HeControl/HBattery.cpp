#include "HBattery_p.h"
#include <QtGui/QPainter>

HE_BEGIN_NAMESPACE

HBattery::HBattery(QWidget *parent) :
    HAnimationProgress(*new HBatteryPrivate, parent)
{
}

HBattery::HBattery(HBatteryPrivate &p, QWidget *parent) :
    HAnimationProgress(p, parent)
{
}

QSize HBattery::sizeHint() const
{
    return {150, 80};
}

QSize HBattery::minimumSizeHint() const
{
    return {30, 10};
}

double HBattery::alarmValue() const
{
    Q_D(const HBattery);
    return d->alarmValue;
}

int HBattery::borderRadius() const
{
    Q_D(const HBattery);
    return d->borderRadius;
}

int HBattery::backgroundRadius() const
{
    Q_D(const HBattery);
    return d->backgroundRadius;
}

int HBattery::headRadius() const
{
    Q_D(const HBattery);
    return d->headRadius;
}

QColor HBattery::borderColorStart() const
{
    Q_D(const HBattery);
    return d->borderColorStart;
}

QColor HBattery::borderColorEnd() const
{
    Q_D(const HBattery);
    return d->borderColorEnd;
}

QColor HBattery::alarmColorStart() const
{
    Q_D(const HBattery);
    return d->alarmColorStart;
}

QColor HBattery::alarmColorEnd() const
{
    Q_D(const HBattery);
    return d->alarmColorEnd;
}

QColor HBattery::normalColorStart() const
{
    Q_D(const HBattery);
    return d->normalColorStart;
}

QColor HBattery::normalColorEnd() const
{
    Q_D(const HBattery);
    return d->normalColorEnd;
}

void HBattery::setAlarmValue(double value)
{
    Q_D(HBattery);
    if (qFuzzyCompare(d->alarmValue, value))
        return;
    d->alarmValue = value;
    update();
}

void HBattery::setBorderRadius(int value)
{
    Q_D(HBattery);
    if (d->borderRadius == value)
        return;
    d->borderRadius = value;
    update();
}

void HBattery::setBackgroundRadius(int value)
{
    Q_D(HBattery);
    if (d->backgroundRadius == value)
        return;
    d->backgroundRadius = value;
    update();
}

void HBattery::setHeadRadius(int value)
{
    Q_D(HBattery);
    if (d->headRadius == value)
        return;
    d->headRadius = value;
    update();
}

void HBattery::setBorderColorStart(const QColor &value)
{
    Q_D(HBattery);
    if (d->borderColorStart == value)
        return;
    d->borderColorStart = value;
    update();
}

void HBattery::setBorderColorEnd(const QColor &value)
{
    Q_D(HBattery);
    if (d->borderColorEnd == value)
        return;
    d->borderColorEnd = value;
    update();
}

void HBattery::setAlarmColorStart(const QColor &value)
{
    Q_D(HBattery);
    if (d->alarmColorStart == value)
        return;
    d->alarmColorStart = value;
    update();
}

void HBattery::setAlarmColorEnd(const QColor &value)
{
    Q_D(HBattery);
    if (d->alarmColorEnd == value)
        return;
    d->alarmColorEnd = value;
    update();
}

void HBattery::setNormalColorStart(const QColor &value)
{
    Q_D(HBattery);
    if (d->normalColorStart == value)
        return;
    d->normalColorStart = value;
    update();
}

void HBattery::setNormalColorEnd(const QColor &value)
{
    Q_D(HBattery);
    if (d->normalColorEnd == value)
        return;
    d->normalColorEnd = value;
    update();
}

void HBattery::paintEvent(QPaintEvent *)
{
    Q_D(HBattery);
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    painter.save();
    // 绘制电池边框
    auto rect1 = QRectF(QPointF(5, 5), QPointF(width() * 9.0 / 10, height() - 5));
    painter.setPen(QPen(d->borderColorStart, 5));
    painter.setBrush(Qt::NoBrush);
    painter.drawRoundRect(rect1, d->borderRadius, d->borderRadius);
    // 绘制电池头部
    auto rect2 = QRectF(QPointF(rect1.right(), height() / 3.0), QPointF(width() - 5, height() * 2.0 / 3));
    auto gradient2 = QLinearGradient(rect2.topLeft(), rect2.bottomLeft());
    gradient2.setColorAt(0.0, d->borderColorStart);
    gradient2.setColorAt(1.0, d->borderColorEnd);
    painter.setBrush(gradient2);
    painter.drawRoundRect(rect2, d->headRadius, d->headRadius);
    // 绘制电量
    auto margin = qMin(width(), height()) / 20;
    auto rect3 = rect1.adjusted(margin, margin, -margin, -margin);
    rect3.setWidth(rect3.width() * d->currentValue / 100);
    auto gradient3 = QLinearGradient(QPointF(0, 0), QPointF(0, height()));
    gradient3.setColorAt(0.0, d->currentValue <= d->alarmValue ? d->alarmColorStart : d->normalColorStart);
    gradient3.setColorAt(1.0, d->currentValue <= d->alarmValue ? d->alarmColorEnd : d->normalColorEnd);
    painter.setPen(Qt::NoPen);
    painter.setBrush(gradient3);
    painter.drawRoundRect(rect3, d->backgroundRadius, d->backgroundRadius);
    painter.restore();
}

HE_END_NAMESPACE
