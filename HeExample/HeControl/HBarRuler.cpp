#include "HBarRuler_p.h"
#include <QtCore/QTimer>
#include <QtGui/QPainter>

HE_CONTROL_BEGIN_NAMESPACE

HBarRuler::HBarRuler(QWidget *parent) :
    HAbstractProgress(*new HBarRulerPrivate, parent)
{
    init();
}

HBarRuler::HBarRuler(HBarRulerPrivate &p, QWidget *parent) :
    HAbstractProgress(p, parent)
{
    init();
}

HBarRuler::~HBarRuler()
{
    Q_D(HBarRuler);
    if (d->timer->isActive())
        d->timer->stop();
}

QSize HBarRuler::sizeHint() const
{
    return {130, 350};
}

QSize HBarRuler::minimumSizeHint() const
{
    return {26, 70};
}

int HBarRuler::longStep() const
{
    Q_D(const HBarRuler);
    return d->longStep;
}

int HBarRuler::shortStep() const
{
    Q_D(const HBarRuler);
    return d->shortStep;
}

int HBarRuler::space() const
{
    Q_D(const HBarRuler);
    return  d->space;
}

bool HBarRuler::isAnimation() const
{
    Q_D(const HBarRuler);
    return d->animation;
}

double HBarRuler::animationStep() const
{
    Q_D(const HBarRuler);
    return d->animationStep;
}

QColor HBarRuler::backgroundStart() const
{
    Q_D(const HBarRuler);
    return d->backgroundStart;
}

QColor HBarRuler::backgroundEnd() const
{
    Q_D(const HBarRuler);
    return d->backgroundEnd;
}

QColor HBarRuler::lineColor() const
{
    Q_D(const HBarRuler);
    return d->lineColor;
}

QColor HBarRuler::barBackground() const
{
    Q_D(const HBarRuler);
    return d->barBackground;
}

QColor HBarRuler::barColor() const
{
    Q_D(const HBarRuler);
    return  d->barColor;
}

void HBarRuler::setValue(double value)
{
    Q_D(HBarRuler);
    if (value < d->minimum || value > d-> maximum || qFuzzyCompare(value, d->value))
        return;
    d->reverse = value < d_ptr->value;
    d->value = value;
    emit valueChanged(value);
    if (!d->animation)
    {
        d->currentValue = value;
        update();
    }
    else
        d->timer->start();
}

// 最大精确度为 3
void HBarRuler::setDecimal(int value)
{
    if (value > 3)
        return;
    HAbstractProgress::setDecimal(value);
}

void HBarRuler::setLongStep(int value)
{
    Q_D(HBarRuler);
    if (value < d->shortStep || d->longStep == value)
        return;
    d->longStep = value;
    update();
}

void HBarRuler::setShortStep(int value)
{
    Q_D(HBarRuler);
    if (value > d->longStep || d->shortStep == value)
        return;
    d->shortStep = value;
    update();
}

void HBarRuler::setSpace(int value)
{
    Q_D(HBarRuler);
    if (d->space == value)
        return;
    d->space = value;
    update();
}

void HBarRuler::setAnimation(bool b)
{
    Q_D(HBarRuler);
    if (d->animation == b)
        return;
    d->animation = b;
    update();
}

void HBarRuler::setAnimationStep(double value)
{
    Q_D(HBarRuler);
    if (qFuzzyCompare(d->animationStep, value))
        return;
    d->animationStep = value;
    update();
}

void HBarRuler::setBackgroundStart(const QColor &value)
{
    Q_D(HBarRuler);
    if (d->backgroundStart == value)
        return;
    d->backgroundStart = value;
    update();
}

void HBarRuler::setBackgroundEnd(const QColor &value)
{
    Q_D(HBarRuler);
    if (d->backgroundEnd == value)
        return;
    d->backgroundEnd = value;
    update();
}

void HBarRuler::setLineColor(const QColor &value)
{
    Q_D(HBarRuler);
    if (d->lineColor == value)
        return;
    d->lineColor = value;
    update();
}

void HBarRuler::setBarBackground(const QColor &value)
{
    Q_D(HBarRuler);
    if (d->barBackground == value)
        return;
    d->barBackground = value;
    update();
}

void HBarRuler::setBarColor(const QColor &value)
{
    Q_D(HBarRuler);
    if (d->barColor == value)
        return;
    d->barColor = value;
    update();
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
    auto gradient = QLinearGradient(QPointF(0, 0), QPointF(0, height()));
    gradient.setColorAt(0.0, backgroundStart());
    gradient.setColorAt(1.0, backgroundEnd());
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(gradient);
    painter->drawRect(rect());
    painter->restore();
}

void HBarRuler::drawRuler(QPainter *painter)
{
    // 长线条短线条长度
    int longLine = 10;
    int shortLine = 7;
    // 绘制纵向标尺线（20的长度为刻度尺文字的宽度）
    double x = space() + 20 + longLine;
    double y = space();
    double increment = (height() - 2 * space()) / range();
    // 根据范围值绘制刻度值及刻度值
    painter->save();
    painter->setPen(lineColor());
    painter->drawLine(QLineF(x, y, x, height() - space()));
    for (int i = maximum(); i >= minimum(); i -= shortStep())
    {
        if (i % longStep() == 0)
        {
            auto text = QString::number(i, 'f', decimal());
            auto fontWidth = painter->fontMetrics().width(text);
            auto fontHeight = painter->fontMetrics().height();
            painter->drawText(x - fontWidth - 15, y + fontHeight / 3.0, text);
            painter->drawLine(x - longLine, y, x, y);
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
    Q_D(HBarRuler);
    // 20的长度为刻度尺文字的宽度 15为刻度尺到柱状图的宽度
    auto x = space() + 20.0 + 15.0;
    auto barRect = QRectF(QPointF(x, space()), QPointF(width() - space(), height() - space()));
    auto y = barRect.bottom() - barRect.height() * toRatio(d->currentValue);
    auto currentRect = QRectF(QPointF(x, y), barRect.bottomRight());
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(barBackground());
    painter->drawRect(barRect);
    painter->setBrush(barColor());
    painter->drawRect(currentRect);
    painter->restore();
}

void HBarRuler::init()
{
    Q_D(HBarRuler);
    d->timer = new QTimer(this);
    d->timer->setInterval(10);
    connect(d->timer, &QTimer::timeout, this, &HBarRuler::updateValue);
    setFont(QFont("Arial", 8));
}

void HBarRuler::updateValue()
{
    Q_D(HBarRuler);
    d->currentValue += d->reverse ? -d->animationStep : d->animationStep;
    if ((d->reverse && d->currentValue <= d->value) || (!d->reverse && d->currentValue >= d->value))
    {
        d->currentValue = d->value;
        d->timer->stop();
    }
    update();
}

HE_CONTROL_END_NAMESPACE
