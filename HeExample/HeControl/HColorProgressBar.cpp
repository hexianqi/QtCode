#include "HColorProgressBar_p.h"
#include <QtGui/QPainter>

HE_CONTROL_BEGIN_NAMESPACE

HColorProgressBar::HColorProgressBar(QWidget *parent) :
    QWidget(parent),
    d_ptr(new HColorProgressBarPrivate)
{
}

HColorProgressBar::HColorProgressBar(HColorProgressBarPrivate &p, QWidget *parent) :
    QWidget(parent),
    d_ptr(&p)
{
}

HColorProgressBar::~HColorProgressBar()
{
}

void HColorProgressBar::setRange(double minimum, double maximum)
{
    if (minimum >= maximum)
        qSwap(minimum, maximum);

    d_ptr->minimum = minimum;
    d_ptr->maximum = maximum;
    if (d_ptr->value < minimum || d_ptr->value > maximum)
        setValue(qBound(minimum, d_ptr->value, maximum));
    else
        update();
}

void HColorProgressBar::setMinimum(double value)
{
    setRange(value, d_ptr->maximum);
}

void HColorProgressBar::setMaximum(double value)
{
    setRange(d_ptr->minimum, value);
}

void HColorProgressBar::setValue(double value)
{
    if (value < d_ptr->minimum || value > d_ptr-> maximum || qFuzzyCompare(value, d_ptr->value))
        return;
    d_ptr->value = value;
    emit valueChanged(value);
    update();
}

void HColorProgressBar::setBarBackground(const QColor &value)
{
    if (d_ptr->barBackground == value)
        return;
    d_ptr->barBackground = value;
    update();
}

void HColorProgressBar::setBarSplitLineColor(const QColor &value)
{
    if (d_ptr->barSplitLineColor == value)
        return;
    d_ptr->barSplitLineColor = value;
    update();
}

void HColorProgressBar::setBarColor(const QColor &value)
{
    if (d_ptr->barColor == value)
        return;
    d_ptr->barColor = value;
    update();
}

void HColorProgressBar::setDecimal(int value)
{
    if (d_ptr->decimal == value)
        return;
    d_ptr->decimal = value;
    update();
}

void HColorProgressBar::setSpace(int value)
{
    if (d_ptr->space == value)
        return;
    d_ptr->space = value;
    update();
}

void HColorProgressBar::setBarSplitLineStep(int value)
{
    if (d_ptr->barSplitLineStep == value)
        return;
    d_ptr->barSplitLineStep = value;
    update();
}

QSize HColorProgressBar::sizeHint() const
{
    return QSize(300, 30);
}

void HColorProgressBar::setShowBarSplitLine(bool value)
{
    if (d_ptr->showBarSplitLine == value)
        return;
    d_ptr->showBarSplitLine = value;
    update();
}

double HColorProgressBar::minimum() const
{
    return d_ptr->minimum;
}

double HColorProgressBar::maximum() const
{
    return d_ptr->maximum;
}

double HColorProgressBar::value() const
{
    return d_ptr->value;
}

QColor HColorProgressBar::barBackground() const
{
    return d_ptr->barBackground;
}

QColor HColorProgressBar::barSplitLineColor() const
{
    return d_ptr->barSplitLineColor;
}

QColor HColorProgressBar::barColor() const
{
    return d_ptr->barColor;
}

int HColorProgressBar::decimal() const
{
    return d_ptr->decimal;
}

int HColorProgressBar::space() const
{
    return d_ptr->space;
}

int HColorProgressBar::barSplitLineStep() const
{
    return d_ptr->barSplitLineStep;
}

bool HColorProgressBar::isShowBarSplitLine() const
{
    return d_ptr->showBarSplitLine;
}

void HColorProgressBar::paintEvent(QPaintEvent *)
{
    auto text = QString("%1%").arg(QString::number(maximum(), 'f', decimal()));
    auto w = QFontMetrics(font()).width(text);
    d_ptr->textRect = QRectF(width() - w - space(), 0, w + space(), height());
    d_ptr->barRect = QRectF(0, 0, width() - w - 2 * space(), height());

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    drawBackground(&painter);
    drawBar(&painter);
    drarBarSplitLine(&painter);
    drawText(&painter);
}

void HColorProgressBar::drawBackground(QPainter *painter)
{
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(barBackground());
    painter->drawRoundedRect(d_ptr->barRect, d_ptr->radiusX, d_ptr->radiusY);
    painter->drawRoundedRect(d_ptr->textRect, d_ptr->radiusX, d_ptr->radiusY);
    painter->restore();
}

void HColorProgressBar::drawBar(QPainter *painter)
{
    auto x = (1 - (value() - minimum()) / (maximum() - minimum())) * d_ptr->barRect.width();
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(barColor());
    painter->drawRoundedRect(d_ptr->barRect.adjusted(0, 0, -x, 0), d_ptr->radiusX, d_ptr->radiusY);
    painter->restore();
}

void HColorProgressBar::drarBarSplitLine(QPainter *painter)
{
    if (!isShowBarSplitLine())
        return;
    auto s = barSplitLineStep() + painter->pen().width();
    painter->save();
    painter->setPen(barSplitLineColor());
    for(int i = 0; i < d_ptr->barRect.right(); i += s)
        painter->drawLine(i, 0, i, height());
    painter->restore();
}

void HColorProgressBar::drawText(QPainter *painter)
{
    auto p = 100.0 * (value() - minimum()) / (maximum() - minimum());
    auto t = QString("%1%").arg(QString::number(p, 'f', decimal()));
    painter->save();
    painter->setPen(palette().text().color());
    painter->drawText(d_ptr->textRect, Qt::AlignCenter, t);
    painter->restore();
}

HE_CONTROL_END_NAMESPACE
