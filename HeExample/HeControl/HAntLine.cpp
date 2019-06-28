#include "HAntLine_p.h"
#include <QtCore/QTimer>
#include <QtGui/QPainter>

HE_CONTROL_BEGIN_NAMESPACE

HAntLine::HAntLine(QWidget *parent) :
    QWidget(parent),
    d_ptr(new HAntLinePrivate)
{
    init();
}

HAntLine::HAntLine(HAntLinePrivate &p, QWidget *parent) :
    QWidget(parent),
    d_ptr(&p)
{
    init();
}

HAntLine::~HAntLine()
{
    if (d_ptr->timer->isActive())
        d_ptr->timer->stop();
}

QSize HAntLine::sizeHint() const
{
    return QSize(100, 100);
}

QSize HAntLine::minimumSizeHint() const
{
    return QSize(20, 20);
}

int HAntLine::lineLength() const
{
    return d_ptr->lineLength;
}

int HAntLine::lineWidth() const
{
    return d_ptr->lineWidth;
}

int HAntLine::lineStep() const
{
    return d_ptr->lineStep;
}

int HAntLine::lineSpeed() const
{
    return d_ptr->lineSpeed;
}

QColor HAntLine::lineColor() const
{
    return d_ptr->lineColor;
}

HAntLine::LineStyle HAntLine::lineStyle() const
{
    return d_ptr->lineStyle;
}

void HAntLine::setLength(int value)
{
    if (d_ptr->lineLength == value)
        return;
    d_ptr->lineLength = value;
    d_ptr->dash = value;
    d_ptr->space = value;
    d_ptr->dashPattern.fill(value, 20);
    update();
}

void HAntLine::setLineWidth(int value)
{
    if (d_ptr->lineWidth == value)
        return;
    d_ptr->lineWidth = value;
    update();
}

void HAntLine::setLineStep(int value)
{
    if (d_ptr->lineStep == value)
        return;
    d_ptr->lineStep = value;
    update();
}

void HAntLine::setLineSpeed(int value)
{
    if (d_ptr->lineSpeed == value)
        return;
    d_ptr->lineSpeed = value;
    update();
}

void HAntLine::setLineColor(const QColor &value)
{
    if (d_ptr->lineColor == value)
        return;
    d_ptr->lineColor = value;
    update();
}

void HAntLine::setLineStyle(LineStyle value)
{
    if (d_ptr->lineStyle == value)
        return;
    d_ptr->lineStyle = value;
    update();
}

void HAntLine::paintEvent(QPaintEvent *)
{
    auto side = qMin(width(), height());
    auto pen = QPen();
    pen.setWidth(d_ptr->lineWidth);
    pen.setColor(d_ptr->lineColor);
    pen.setDashPattern(d_ptr->dashPattern);

    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing);
    painter.setPen(pen);
    if (d_ptr->lineStyle == Rect)
        painter.drawRect(rect());
    if (d_ptr->lineStyle == RoundedRect)
        painter.drawRoundedRect(rect(), 5, 5);
    if (d_ptr->lineStyle == Ellipse)
        painter.drawEllipse(rect());
    if (d_ptr->lineStyle == Circle)
        painter.drawEllipse(width() / 2 - side / 2, 0, side, side);
}

void HAntLine::init()
{
    d_ptr->dashPattern.fill(d_ptr->lineLength, 20);
    d_ptr->timer = new QTimer(this);
    connect(d_ptr->timer, &QTimer::timeout, this, &HAntLine::updateValue);
    d_ptr->timer->start(d_ptr->lineSpeed);
}

void HAntLine::updateValue()
{
    // 当蚂蚁线走到末尾,则重新赋值
    if (d_ptr->dash >= d_ptr->lineLength && d_ptr->space >= d_ptr->lineLength)
    {
        d_ptr->dash = 0;
        d_ptr->space = 0;
    }

    if (d_ptr->dash == 0 && d_ptr->space < d_ptr->lineLength)
        d_ptr->space += d_ptr->lineStep;
    else if (d_ptr->space >= d_ptr->lineLength && d_ptr->dash < d_ptr->lineLength)
        d_ptr->dash += d_ptr->lineStep;

    // 每次只需要将前面两个长度更新就行
    d_ptr->dashPattern[0] = d_ptr->dash;
    d_ptr->dashPattern[1] = d_ptr->space;
    update();
}

HE_CONTROL_END_NAMESPACE
