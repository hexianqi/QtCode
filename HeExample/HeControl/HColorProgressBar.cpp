#include "HColorProgressBar_p.h"
#include <QtGui/QPainter>

HE_CONTROL_BEGIN_NAMESPACE

HColorProgressBar::HColorProgressBar(QWidget *parent) :
    HAbstractProgress(*new HColorProgressBarPrivate, parent)
{
}

HColorProgressBar::HColorProgressBar(HColorProgressBarPrivate &p, QWidget *parent) :
    HAbstractProgress(p, parent)
{
}

HColorProgressBar::~HColorProgressBar()
{
}

QSize HColorProgressBar::sizeHint() const
{
    return QSize(300, 30);
}

QColor HColorProgressBar::barBackground() const
{
    Q_D(const HColorProgressBar);
    return d->barBackground;
}

QColor HColorProgressBar::barSplitLineColor() const
{
    Q_D(const HColorProgressBar);
    return d->barSplitLineColor;
}

QColor HColorProgressBar::barColor() const
{
    Q_D(const HColorProgressBar);
    return d->barColor;
}

int HColorProgressBar::space() const
{
    Q_D(const HColorProgressBar);
    return d->space;
}

int HColorProgressBar::barSplitLineStep() const
{
    Q_D(const HColorProgressBar);
    return d->barSplitLineStep;
}

bool HColorProgressBar::isShowBarSplitLine() const
{
    Q_D(const HColorProgressBar);
    return d->showBarSplitLine;
}


void HColorProgressBar::setBarBackground(const QColor &value)
{
    Q_D(HColorProgressBar);
    if (d->barBackground == value)
        return;
    d->barBackground = value;
    update();
}

void HColorProgressBar::setBarSplitLineColor(const QColor &value)
{
    Q_D(HColorProgressBar);
    if (d->barSplitLineColor == value)
        return;
    d->barSplitLineColor = value;
    update();
}

void HColorProgressBar::setBarColor(const QColor &value)
{
    Q_D(HColorProgressBar);
    if (d->barColor == value)
        return;
    d->barColor = value;
    update();
}

void HColorProgressBar::setSpace(int value)
{
    Q_D(HColorProgressBar);
    if (d->space == value)
        return;
    d->space = value;
    update();
}

void HColorProgressBar::setBarSplitLineStep(int value)
{
    Q_D(HColorProgressBar);
    if (d->barSplitLineStep == value)
        return;
    d->barSplitLineStep = value;
    update();
}

void HColorProgressBar::setShowBarSplitLine(bool value)
{
    Q_D(HColorProgressBar);
    if (d->showBarSplitLine == value)
        return;
    d->showBarSplitLine = value;
    update();
}

void HColorProgressBar::paintEvent(QPaintEvent *)
{
    Q_D(HColorProgressBar);
    auto side = qMin(width(), height());
    auto f = font();
    f.setPixelSize(side / 2);
    auto text = QString("%1%").arg(QString::number(maximum(), 'f', decimal()));
    auto w = QFontMetrics(f).width(text);

    d->textRect = QRectF(width() - w - space(), 0, w + space(), height());
    d->barRect = QRectF(0, 0, width() - w - 2 * space(), height());

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setFont(f);
    drawBackground(&painter);
    drawBar(&painter);
    drarBarSplitLine(&painter);
    drawText(&painter);
}

void HColorProgressBar::drawBackground(QPainter *painter)
{
    Q_D(HColorProgressBar);
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(barBackground());
    painter->drawRoundedRect(d->barRect, d->radiusX, d->radiusY);
    painter->drawRoundedRect(d->textRect, d->radiusX, d->radiusY);
    painter->restore();
}

void HColorProgressBar::drawBar(QPainter *painter)
{
    Q_D(HColorProgressBar);
    auto x = (1 - toRatio(d->value)) * d->barRect.width();
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(barColor());
    painter->drawRoundedRect(d->barRect.adjusted(0, 0, -x, 0), d->radiusX, d->radiusY);
    painter->restore();
}

void HColorProgressBar::drarBarSplitLine(QPainter *painter)
{
    Q_D(HColorProgressBar);
    if (!isShowBarSplitLine())
        return;
    auto s = barSplitLineStep() + painter->pen().width();
    painter->save();
    painter->setPen(barSplitLineColor());
    for(int i = 0; i < d->barRect.right(); i += s)
        painter->drawLine(i, 0, i, height());
    painter->restore();
}

void HColorProgressBar::drawText(QPainter *painter)
{
    Q_D(HColorProgressBar);
    auto p = 100.0 * toRatio(d->value);
    auto t = QString("%1%").arg(QString::number(p, 'f', decimal()));
    painter->save();
    painter->setPen(palette().text().color());
    painter->drawText(d->textRect, Qt::AlignCenter, t);
    painter->restore();
}

HE_CONTROL_END_NAMESPACE
