#include "HBarRuler_p.h"
#include <QtCore/QTimer>
#include <QtGui/QPainter>

HE_CONTROL_BEGIN_NAMESPACE

void HBarRulerPrivate::updateValue()
{
    if (!reverse)
    {
        currentValue += animationStep;
        if (currentValue >= value)
        {
            currentValue = value;
            timer->stop();
        }
    }
    else
    {
        currentValue -= animationStep;
        if (currentValue <= value)
        {
            currentValue = value;
            timer->stop();
        }
    }
}

HBarRuler::HBarRuler(QWidget *parent) :
    QWidget(parent),
    d_ptr(new HBarRulerPrivate)
{
    init();
}

HBarRuler::HBarRuler(HBarRulerPrivate &p, QWidget *parent) :
    QWidget(parent),
    d_ptr(&p)
{
    init();
}

HBarRuler::~HBarRuler()
{
    if (d_ptr->timer->isActive())
        d_ptr->timer->stop();
}

void HBarRuler::setRange(double minValue, double maxValue)
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

void HBarRuler::setMinValue(double value)
{
    setRange(value, d_ptr->maxValue);
}

void HBarRuler::setMaxValue(double value)
{
    setRange(d_ptr->minValue, value);
}

void HBarRuler::setValue(double value)
{
    if (value < d_ptr->minValue || value >d_ptr-> maxValue)
        return;
    d_ptr->reverse = value < d_ptr->value;
    d_ptr->value = value;
    emit valueChanged(value);
    if (!isAnimation())
    {
        d_ptr->currentValue = value;
        update();
    }
    else
        d_ptr->timer->start();
}

// 最大精确度为 3
void HBarRuler::setPrecision(int value)
{
    if (value > 3 || d_ptr->precision == value)
        return;
    d_ptr->precision = value;
    update();
}

void HBarRuler::setLongStep(int value)
{
    if (value < d_ptr->shortStep || d_ptr->longStep == value)
        return;
    d_ptr->longStep = value;
    update();
}

void HBarRuler::setShortStep(int value)
{
    if (value > d_ptr->longStep || d_ptr->shortStep == value)
        return;
    d_ptr->shortStep = value;
    update();
}

void HBarRuler::setSpace(int value)
{
    if (d_ptr->space == value)
        return;
    d_ptr->space = value;
    update();
}

void HBarRuler::setAnimation(bool b)
{
    if (d_ptr->animation == b)
        return;
    d_ptr->animation = b;
    update();
}

void HBarRuler::setAnimationStep(double value)
{
    if (d_ptr->animationStep == value)
        return;
    d_ptr->animationStep = value;
    update();
}

void HBarRuler::setBackgroundStart(QColor value)
{
    if (d_ptr->backgroundStart == value)
        return;
    d_ptr->backgroundStart = value;
    update();
}

void HBarRuler::setBackgroundEnd(QColor value)
{
    if (d_ptr->backgroundEnd == value)
        return;
    d_ptr->backgroundEnd = value;
    update();
}

void HBarRuler::setLineColor(QColor value)
{
    if (d_ptr->lineColor == value)
        return;
    d_ptr->lineColor = value;
    update();
}

void HBarRuler::setBarBackground(QColor value)
{
    if (d_ptr->barBackground == value)
        return;
    d_ptr->barBackground = value;
    update();
}

void HBarRuler::setBarColor(QColor value)
{
    if (d_ptr->barColor == value)
        return;
    d_ptr->barColor = value;
    update();
}

QSize HBarRuler::sizeHint() const
{
    return QSize(100, 350);
}

QSize HBarRuler::minimumSizeHint() const
{
    return QSize(20, 50);
}

double HBarRuler::minValue() const
{
    return d_ptr->minValue;
}

double HBarRuler::maxValue() const
{
    return d_ptr->maxValue;
}

double HBarRuler::value() const
{
    return d_ptr->value;
}

int HBarRuler::precision() const
{
    return d_ptr->precision;
}

int HBarRuler::longStep() const
{
    return d_ptr->longStep;
}

int HBarRuler::shortStep() const
{
    return d_ptr->shortStep;
}

int HBarRuler::space() const
{
    return  d_ptr->space;
}

bool HBarRuler::isAnimation() const
{
    return d_ptr->animation;
}

double HBarRuler::animationStep() const
{
    return d_ptr->animationStep;
}

QColor HBarRuler::backgroundStart() const
{
    return d_ptr->backgroundStart;
}

QColor HBarRuler::backgroundEnd() const
{
    return d_ptr->backgroundEnd;
}

QColor HBarRuler::lineColor() const
{
    return d_ptr->lineColor;
}

QColor HBarRuler::barBackground() const
{
    return d_ptr->barBackground;
}

QColor HBarRuler::barColor() const
{
    return  d_ptr->barColor;
}

void HBarRuler::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    drawBackground(&painter);
    drawRuler(&painter);
    drawBar(&painter);
}

void HBarRuler::drawBackground(QPainter *painter)
{
    painter->save();
    painter->setPen(Qt::NoPen);
    auto gradient = QLinearGradient(QPointF(0, 0), QPointF(0, height()));
    gradient.setColorAt(0.0, backgroundStart());
    gradient.setColorAt(1.0, backgroundEnd());
    painter->setBrush(gradient);
    painter->drawRect(rect());
    painter->restore();
}

void HBarRuler::drawRuler(QPainter *painter)
{
    painter->save();
    painter->setPen(lineColor());

    // 长线条短线条长度
    int longLine = 10;
    int shortLine = 7;
    // 绘制纵向标尺线（20的长度为刻度尺文字的宽度）
    auto x = space() + 20 + longLine;
    auto y = space();
    // 每一格移动多少
    auto increment = (height() - 2 * space()) / (maxValue() - minValue());

    // 根据范围值绘制刻度值及刻度值
    painter->drawLine(QLineF(x, y, x, height() - space()));
    for (int i = maxValue(); i >= minValue(); i = i - shortStep())
    {
        if (i % longStep() == 0)
        {
            QString text = QString("%1").arg((double)i, 0, 'f', precision());
            double fontWidth = painter->fontMetrics().width(text);
            double fontHeight = painter->fontMetrics().height();
            painter->drawText(x - fontWidth - 15, y + fontHeight / 3, text);
            painter->drawLine(QLineF(x - longLine, y, x, y));
        }
        else
        {
            shortLine = i % (longStep() / 2) == 0 ? 7 : 4;
            painter->drawLine(QLineF(x - shortLine, y, x, y));
        }
        y += increment * shortStep();
    }
    painter->restore();
}

void HBarRuler::drawBar(QPainter *painter)
{
    painter->save();
    painter->setPen(Qt::NoPen);

    // 20的长度为刻度尺文字的宽度 15为刻度尺到柱状图的宽度
    auto x = space() + 20.0 + 15.0;
    auto barRect = QRectF(QPointF(x, space()), QPointF(width() - space(), height() - space()));
    auto y = barRect.bottom() - barRect.height() * (d_ptr->currentValue - minValue())  / (maxValue() - minValue());
    auto currentRect = QRectF(QPointF(x, y), barRect.bottomRight());
    painter->setBrush(barBackground());
    painter->drawRect(barRect);
    painter->setBrush(barColor());
    painter->drawRect(currentRect);
    painter->restore();
}

void HBarRuler::init()
{
    d_ptr->timer = new QTimer(this);
    d_ptr->timer->setInterval(10);
    connect(d_ptr->timer, &QTimer::timeout, this, &HBarRuler::animationUpdate);
    setFont(QFont("Arial", 8));
}

void HBarRuler::animationUpdate()
{
    d_ptr->updateValue();
    update();
}

HE_CONTROL_END_NAMESPACE
