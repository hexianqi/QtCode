#include "HThermometerRuler_p.h"
#include <QtGui/QPainter>

HE_CONTROL_BEGIN_NAMESPACE

HThermometerRuler::HThermometerRuler(QWidget *parent) :
    HAnimationProgress(*new HThermometerRulerPrivate, parent)
{
}

HThermometerRuler::HThermometerRuler(HThermometerRulerPrivate &p, QWidget *parent) :
    HAnimationProgress(p, parent)
{
}

HThermometerRuler::~HThermometerRuler()
{
}

QSize HThermometerRuler::sizeHint() const
{
    return QSize(130, 350);
}

QSize HThermometerRuler::minimumSizeHint() const
{
    return QSize(26, 70);
}

int HThermometerRuler::longStep() const
{
    Q_D(const HThermometerRuler);
    return d->longStep;
}

int HThermometerRuler::shortStep() const
{
    Q_D(const HThermometerRuler);
    return d->shortStep;
}

int HThermometerRuler::space() const
{
    Q_D(const HThermometerRuler);
    return  d->space;
}

bool HThermometerRuler::isShowUserValue() const
{
    Q_D(const HThermometerRuler);
    return d->showUserValue;
}

double HThermometerRuler::userValue() const
{
    Q_D(const HThermometerRuler);
    return d->userValue;
}

QColor HThermometerRuler::userValueColor() const
{
    Q_D(const HThermometerRuler);
    return d->userValueColor;
}

QColor HThermometerRuler::backgroundStart() const
{
    Q_D(const HThermometerRuler);
    return d->backgroundStart;
}

QColor HThermometerRuler::backgroundEnd() const
{
    Q_D(const HThermometerRuler);
    return d->backgroundEnd;
}

QColor HThermometerRuler::lineColor() const
{
    Q_D(const HThermometerRuler);
    return d->lineColor;
}

QColor HThermometerRuler::barBackground() const
{
    Q_D(const HThermometerRuler);
    return d->barBackground;
}

QColor HThermometerRuler::barColor() const
{
    Q_D(const HThermometerRuler);
    return d->barColor;
}

HThermometerRuler::BarPosition HThermometerRuler::barPosition() const
{
    Q_D(const HThermometerRuler);
    return d->barPosition;
}

HThermometerRuler::TickPosition HThermometerRuler::tickPosition() const
{
    Q_D(const HThermometerRuler);
    return d->tickPosition;
}

void HThermometerRuler::setLongStep(int value)
{
    Q_D(HThermometerRuler);
    if (value < d->shortStep || d->longStep == value)
        return;
    d->longStep = value;
    update();
}

void HThermometerRuler::setShortStep(int value)
{
    Q_D(HThermometerRuler);
    if (value > d->longStep || d->shortStep == value)
        return;
    d->shortStep = value;
    update();
}

void HThermometerRuler::setSpace(int value)
{
    Q_D(HThermometerRuler);
    if (d->space == value)
        return;
    d->space = value;
    update();
}

void HThermometerRuler::setShowUserValue(bool b)
{
    Q_D(HThermometerRuler);
    if (d->showUserValue == b)
        return;
    d->showUserValue = b;
    update();
}

void HThermometerRuler::setUserValue(double value)
{
    Q_D(HThermometerRuler);
    if (qFuzzyCompare(d->userValue, value))
        return;
    d->userValue = value;
    update();
}

void HThermometerRuler::setUserValueColor(const QColor &value)
{
    Q_D(HThermometerRuler);
    if (d->userValueColor == value)
        return;
    d->userValueColor = value;
    update();
}

void HThermometerRuler::setBackgroundStart(const QColor &value)
{
    Q_D(HThermometerRuler);
    if (d->backgroundStart == value)
        return;
    d->backgroundStart = value;
    update();
}

void HThermometerRuler::setBackgroundEnd(const QColor &value)
{
    Q_D(HThermometerRuler);
    if (d->backgroundEnd == value)
        return;
    d->backgroundEnd = value;
    update();
}

void HThermometerRuler::setLineColor(const QColor &value)
{
    Q_D(HThermometerRuler);
    if (d->lineColor == value)
        return;
    d->lineColor = value;
    update();
}

void HThermometerRuler::setBarBackground(const QColor &value)
{
    Q_D(HThermometerRuler);
    if (d->barBackground == value)
        return;
    d->barBackground = value;
    update();
}

void HThermometerRuler::setBarColor(const QColor &value)
{
    Q_D(HThermometerRuler);
    if (d->barColor == value)
        return;
    d->barColor = value;
    update();
}

void HThermometerRuler::setBarPosition(BarPosition value)
{
    Q_D(HThermometerRuler);
    if (d->barPosition == value)
        return;
    d->barPosition = value;
    update();
}

void HThermometerRuler::setTickPosition(TickPosition value)
{
    Q_D(HThermometerRuler);
    if (d->tickPosition == value)
        return;
    d->tickPosition = value;
    update();
}

void HThermometerRuler::resizeEvent(QResizeEvent *)
{
    Q_D(HThermometerRuler);
    auto side = qMin(width(), height());
    d->radius = side / 5;
    d->barWidth = side / 8;
    d->barHeight = height() - d->space - d->radius * 2 - 2;
    d->targetX = rect().center().x();
    d->barRect = QRectF(d->targetX - d->barWidth / 2, d->space, d->barWidth, d->barHeight + 5);
    d->circleRect = QRectF(d->targetX - d->radius, height() - d->radius * 2 - 2, d->radius * 2, d->radius * 2);
}

void HThermometerRuler::paintEvent(QPaintEvent *)
{
    Q_D(HThermometerRuler);
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    // 绘制背景
    drawBackground(&painter);
    // 绘制标尺及刻度尺
    if (d->tickPosition == TickPosition_Left || d->tickPosition == TickPosition_Both)
        drawRuler(&painter, 0);
   if (d->tickPosition == TickPosition_Right || d->tickPosition == TickPosition_Both)
        drawRuler(&painter, 1);
    // 绘制水银柱背景,包含水银柱底部圆
    drawBarBackground(&painter);
    // 绘制当前水银柱,包含水银柱底部圆
    drawBar(&painter);
    // 绘制当前值
    drawValue(&painter);
}

void HThermometerRuler::drawBackground(QPainter *painter)
{
    Q_D(HThermometerRuler);
    auto gradient = QLinearGradient(QPointF(0, 0), QPointF(0, height()));
    gradient.setColorAt(0.0, d->backgroundStart);
    gradient.setColorAt(1.0, d->backgroundEnd);
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(gradient);
    painter->drawRect(rect());
    painter->restore();
}

void HThermometerRuler::drawBarBackground(QPainter *painter)
{
    Q_D(HThermometerRuler);
    QPainterPath path;
    path.addRect(d->barRect);
    path.addEllipse(d->circleRect);
    path.setFillRule(Qt::WindingFill);
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(d->barBackground);
    painter->drawPath(path);
    painter->restore();
}

void HThermometerRuler::drawRuler(QPainter *painter, int type)
{
    Q_D(HThermometerRuler);
    // 长线条短线条长度
    int longLine = 10;
    int shortLine = 7;
    // 绘制纵向标尺线 偏移 5 像素
    int offset = d->barWidth / 2 + 5;
    int barPercent = qMax(2, d->barWidth / 8);
    double increment = (height() - 2 * d->space - 2 * d->radius) / range();
    // 左侧刻度尺需要重新计算
    if (type == 0)
    {
        offset = -offset;
        longLine = -longLine;
        shortLine = -shortLine;
    }
    double x = d->targetX + offset;
    double y = d->space + barPercent;

    // 根据范围值绘制刻度值及刻度值
    painter->save();
    painter->setPen(d->lineColor);
    painter->drawLine(QLineF(x, y, x, height() - 2 * d->radius - 5));
    for (int i = d->maximum; i >= d->minimum; i -= d->shortStep)
    {
        if (i % d->longStep == 0)
        {
            auto text = QString::number(i, 'f', d->decimal);
            auto fontHeight = painter->fontMetrics().height();
            painter->drawLine(QLineF(x + longLine, y, x, y));
            if (type == 0)
                painter->drawText(QRectF(x - 45, y - fontHeight / 3, 30, 15), Qt::AlignRight, text);
            if (type == 1)
                painter->drawText(QRectF(x + longLine + 5, y - fontHeight / 3, 30, 15), Qt::AlignLeft, text);
        }
        else
            painter->drawLine(QLineF(x + shortLine, y, x, y));
        y += increment * d->shortStep;
    }
    painter->restore();
}

void HThermometerRuler::drawBar(QPainter *painter)
{
    Q_D(HThermometerRuler);
    int barPercent = qMax(2, d->barWidth / 8);
    int circlePercent = qMax(2, d->radius / 6);
    double increment = (height() - 2 * d->space - 2 * d->radius) / range();
    double rulerHeight = height() - d->space - 2 * d->radius;
    double barX = d->targetX - d->barWidth / 2;
    double barY = rulerHeight - (d->currentValue - d->minimum) * increment;
    QPainterPath path;
    path.addRect(QRectF(barX + barPercent, barY + barPercent, d->barWidth - barPercent * 2, d->barHeight + d->radius - barY));
    path.addEllipse(d->circleRect.adjusted(circlePercent, circlePercent, -circlePercent, -circlePercent));
    path.setFillRule(Qt::WindingFill);

    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(d->barColor);
    painter->drawPath(path);
    // 绘制用户设定值三角号
    if (d->showUserValue)
    {
        int offset = 15;
        painter->setBrush(d->userValueColor);
        if (d->tickPosition == TickPosition_Left || d->tickPosition == TickPosition_Both)
        {
            QPolygonF pts;
            double initX = d->targetX - (d->barWidth / 2 + 5);
            double initY = rulerHeight - (d->userValue - d->minimum) * increment + barPercent;
            pts << QPointF(initX, initY);
            pts << QPointF(initX - offset, initY - offset / 2);
            pts << QPointF(initX - offset, initY + offset / 2);
            painter->drawPolygon(pts);
        }
        if (d->tickPosition == TickPosition_Right || d->tickPosition == TickPosition_Both)
        {
            QPolygonF pts;
            double initX = d->targetX + (d->barWidth / 2 + 5);
            double initY = rulerHeight - (d->userValue - d->minimum) * increment + barPercent;
            pts << QPointF(initX, initY);
            pts << QPointF(initX + offset, initY - offset / 2);
            pts << QPointF(initX + offset, initY + offset / 2);
            painter->drawPolygon(pts);
        }
    }
    painter->restore();
}

void HThermometerRuler::drawValue(QPainter *painter)
{
    Q_D(HThermometerRuler);
    auto text = QString::number(d->currentValue, 'f', d->decimal);
    auto f = font();
    f.setPointSizeF(d->circleRect.width() * 0.5);
    painter->save();
    painter->setFont(f);
    painter->setPen(Qt::white);
    painter->drawText(d->circleRect, Qt::AlignCenter, text);
    painter->restore();
}

HE_CONTROL_END_NAMESPACE
