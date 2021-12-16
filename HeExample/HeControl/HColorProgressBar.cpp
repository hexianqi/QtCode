#include "HColorProgressBar_p.h"
#include "HDrawHelper.h"
#include <QtGui/QPainter>

HE_BEGIN_NAMESPACE

HColorProgressBar::HColorProgressBar(QWidget *parent) :
    HAbstractProgress(*new HColorProgressBarPrivate, parent)
{
}

HColorProgressBar::HColorProgressBar(HColorProgressBarPrivate &p, QWidget *parent) :
    HAbstractProgress(p, parent)
{
}

QSize HColorProgressBar::sizeHint() const
{
    return {300, 30};
}

int HColorProgressBar::radius() const
{
    Q_D(const HColorProgressBar);
    return d->radius;
}

HColorProgressBar::TextPosition HColorProgressBar::textPosition() const
{
    Q_D(const HColorProgressBar);
    return d->textPosition;
}

QColor HColorProgressBar::textForeColor() const
{
    Q_D(const HColorProgressBar);
    return d->textForeColor;
}

QColor HColorProgressBar::textBackColor() const
{
    Q_D(const HColorProgressBar);
    return d->textBackColor;
}

HColorProgressBar::BarStyle HColorProgressBar::barStyle() const
{
    Q_D(const HColorProgressBar);
    return d->barStyle;
}

QColor HColorProgressBar::barForeColor() const
{
    Q_D(const HColorProgressBar);
    return d->barForeColor;
}

QColor HColorProgressBar::barForeAlternateColor() const
{
    Q_D(const HColorProgressBar);
    return d->barForeAlternateColor;
}

QColor HColorProgressBar::barBackColor() const
{
    Q_D(const HColorProgressBar);
    return d->barBackColor;
}

int HColorProgressBar::barStepSpace() const
{
    Q_D(const HColorProgressBar);
    return d->barStepSpace;
}

int HColorProgressBar::barStepDelta() const
{
    Q_D(const HColorProgressBar);
    return d->barStepDelta;
}

int HColorProgressBar::barStepSize() const
{
    Q_D(const HColorProgressBar);
    return d->barStepSize;
}

void HColorProgressBar::setRadius(int value)
{
    Q_D(HColorProgressBar);
    if (d->radius == value)
        return;
    d->radius = value;
    update();
}

void HColorProgressBar::setTextPosition(HColorProgressBar::TextPosition value)
{
    Q_D(HColorProgressBar);
    if (d->textPosition == value)
        return;
    d->textPosition = value;
    update();
}

void HColorProgressBar::setTextForeColor(const QColor &value)
{
    Q_D(HColorProgressBar);
    if (d->textForeColor == value)
        return;
    d->textForeColor = value;
    update();
}

void HColorProgressBar::setTextBackColor(const QColor &value)
{
    Q_D(HColorProgressBar);
    if (d->textBackColor == value)
        return;
    d->textBackColor = value;
    update();
}

void HColorProgressBar::setBarStyle(HColorProgressBar::BarStyle value)
{
    Q_D(HColorProgressBar);
    if (d->barStyle == value)
        return;
    d->barStyle = value;
    update();
}

void HColorProgressBar::setBarForeColor(const QColor &value)
{
    Q_D(HColorProgressBar);
    if (d->barForeColor == value)
        return;
    d->barForeColor = value;
    update();
}

void HColorProgressBar::setBarForeAlternateColor(const QColor &value)
{
    Q_D(HColorProgressBar);
    if (d->barForeAlternateColor == value)
        return;
    d->barForeAlternateColor = value;
    update();
}

void HColorProgressBar::setBarBackColor(const QColor &value)
{
    Q_D(HColorProgressBar);
    if (d->barBackColor == value)
        return;
    d->barBackColor = value;
    update();
}

void HColorProgressBar::setBarStepSpace(int value)
{
    Q_D(HColorProgressBar);
    if (d->barStepSpace == value)
        return;
    d->barStepSpace = value;
    update();
}

void HColorProgressBar::setBarStepDelta(int value)
{
    Q_D(HColorProgressBar);
    if (d->barStepDelta == value)
        return;
    d->barStepDelta = value;
    update();
}

void HColorProgressBar::setBarStepSize(int value)
{
    Q_D(HColorProgressBar);
    if (d->barStepSize == value)
        return;
    d->barStepSize = value;
    if (value > 2)
        d->radius = 0;
    update();
}

void HColorProgressBar::setBarForeDataColors(const QGradientStops &value)
{
    Q_D(HColorProgressBar);
    if (d->gradientData == value)
        return;
    d->gradientData = value;
    update();
}

void HColorProgressBar::paintEvent(QPaintEvent *)
{
    Q_D(HColorProgressBar);

    QRectF barRect, textRect;
    auto curPos = toRatio(d->value) * width();
    auto text = QString("%1%").arg(QString::number(maximum(), 'f', decimal()));

    if (d->textPosition == TextPosition_OutBar)
    {
        barRect = QRectF(0, 0, 0.85 * width(), height());
        textRect = QRectF(0.85 * width(), 0, 0.15 * width(), height());
    }
    else if (d->textPosition == TextPosition_InBar)
    {
        barRect = QRectF(0, 0, width(), height());
        textRect = QRectF(curPos - 0.15 * width(), 0, 0.15 * width(), height());
    }
    else if (d->textPosition == TextPosition_OnBar)
    {
        barRect = QRectF(0, height() * 7 / 12.0, width(), height() / 3.0);
        if (curPos < 0.9 * width())
        {
            auto offset = qMin(15.0, curPos);
            textRect = QRectF(curPos - offset, height() / 12.0, 0.15 * width(), height() * 5 / 12.0);
        }
        else
            textRect = QRectF(0.85 * width(), height() / 12.0, 0.15 * width(), height() * 5 / 12.0);
    }

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    auto f = HDrawHelper::adjustFontSize(&painter, text, textRect.width());
    painter.setFont(f);

    drawBarBackground(&painter, barRect);
    drawData(&painter, barRect);
    drawTextBackground(&painter, textRect);
    drawText(&painter, textRect);
}

void HColorProgressBar::drawBarBackground(QPainter *painter, QRectF rect)
{
    Q_D(HColorProgressBar);
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(d->barBackColor);
    painter->drawRoundedRect(rect, d->radius, d->radius);
    painter->restore();
}

void HColorProgressBar::drawTextBackground(QPainter *painter, QRectF rect)
{
    Q_D(HColorProgressBar);
    if (d->textPosition == TextPosition_InBar)
        return;

    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(QBrush(d->textBackColor));
    if (d->textPosition == TextPosition_OnBar)
    {
        auto curPos = toRatio(d->value) * width();
        auto length = qMin(width(), height());
        auto radius = qMin(length, 10) / 2.0;
        painter->drawRoundedRect(rect, 3, 3);
        painter->drawEllipse(QPointF(curPos - 2 * radius, height() * 9 / 12.0), radius, radius);
    }
    if (d->textPosition == TextPosition_OutBar)
        painter->drawRoundedRect(rect, d->radius, d->radius);
    painter->restore();
}

/******************************************************************************
 *
 * min                                          value        max
 *  |--------------------------------------------|------------|
 *  =================== rect ====================|
 *  ---------------------------------------------|------------|
 *  |                                            |<--- dx --->|
 *
******************************************************************************/
void HColorProgressBar::drawData(QPainter *painter, QRectF rect)
{
    Q_D(HColorProgressBar);
    auto dx = (1.0 - toRatio(d->value)) * rect.width();
    rect.adjust(0, 0, -dx, 0);

    painter->save();
    painter->setPen(Qt::NoPen);
    if (d->barStyle == BarStyle_Gradual)
    {
        auto gradient = QLinearGradient(rect.x(), rect.y(), rect.width(), rect.height());
        for (int i = 0; i < d->gradientData.count(); i++)
            gradient.setColorAt(d->gradientData.at(i).first, d->gradientData.at(i).second);
        painter->setBrush(gradient);
        painter->setPen(Qt::transparent);
        painter->drawRoundedRect(rect, d->radius, d->radius);
    }
    else
    {
        painter->setBrush(QBrush(d->barForeColor));
        painter->drawRoundedRect(rect, d->radius, d->radius);
    }
    painter->restore();
    drawBarStep(painter, rect);
}

/******************************************************************************
 *                        space                            size
 *                    -->|    |<--                      x1 x2
 *  ---------------------|----|------------------   -----|-|-----
 *                 /|   /    /                          /=/
 *                / |  /    /                          /=/
 *  -------------|--|----------------------------   --|-|--------
 *            -->|  |<--                             x4 x3
 *              delta
 ******************************************************************************/
void HColorProgressBar::drawBarStep(QPainter *painter, QRectF rect)
{
    Q_D(HColorProgressBar);
    if (d->barStyle != BarStyle_Segmented)
        return;

    painter->save();
    if (d->barStepSize < 3)
    {
        painter->setPen(QPen(d->barForeAlternateColor, d->barStepSize));
        for (int i = 0; i < rect.right(); i += d->barStepSize + d->barStepSpace)
            painter->drawLine(QPointF(i, rect.top()), QPointF(i + d->barStepDelta, rect.bottom()));
    }
    else
    {
        painter->setPen(Qt::NoPen);
        painter->setBrush(d->barForeAlternateColor);
        for (int i = 0; i < rect.right(); i += d->barStepSize + d->barStepSpace)
        {
            double x1 = i;
            double x2 = i + d->barStepSize;
            double x3 = i + d->barStepSize + d->barStepDelta;
            double x4 = i + d->barStepDelta;
            x2 = qBound(0.0, x2, rect.right());
            x3 = qBound(0.0, x3, rect.right());
            x4 = qBound(0.0, x4, rect.right());
            painter->drawPolygon(QPolygonF() << QPointF(x1, rect.top()) << QPointF(x2, rect.top()) << QPointF(x3, rect.bottom()) << QPointF(x4, rect.bottom()));
       }
    }
    painter->restore();
}

void HColorProgressBar::drawText(QPainter *painter, QRectF rect)
{
    Q_D(HColorProgressBar);
    auto p = 100.0 * toRatio(d->value);
    auto t = QString("%1%").arg(QString::number(p, 'f', decimal()));
    painter->save();
    painter->setPen(palette().text().color());
    painter->drawText(rect, Qt::AlignCenter, t);
    painter->restore();
}

//void HColorProgressBar::paintEvent(QPaintEvent *)
//{
//    Q_D(HColorProgressBar);
//    auto side = qMin(width(), height());
//    auto f = font();
//    f.setPixelSize(side / 2);
//    auto text = QString("%1%").arg(QString::number(maximum(), 'f', decimal()));
//    auto w = QFontMetrics(f).width(text);

//    d->textRect = QRectF(width() - w - space(), 0, w + space(), height());
//    d->barRect = QRectF(0, 0, width() - w - 2 * space(), height());

//    QPainter painter(this);
//    painter.setRenderHint(QPainter::Antialiasing);
//    painter.setFont(f);
//    drawBackground(&painter);
//    drawBar(&painter);
//    drarBarSplitLine(&painter);
//    drawText(&painter);
//}

//void HColorProgressBar::drawBackground(QPainter *painter)
//{
//    Q_D(HColorProgressBar);
//    painter->save();
//    painter->setPen(Qt::NoPen);
//    painter->setBrush(barBackground());
//    painter->drawRoundedRect(d->barRect, d->radiusX, d->radiusY);
//    painter->drawRoundedRect(d->textRect, d->radiusX, d->radiusY);
//    painter->restore();
//}

//void HColorProgressBar::drawBar(QPainter *painter)
//{
//    Q_D(HColorProgressBar);
//    auto x = (1 - toRatio(d->value)) * d->barRect.width();
//    painter->save();
//    painter->setPen(Qt::NoPen);
//    painter->setBrush(barColor());
//    painter->drawRoundedRect(d->barRect.adjusted(0, 0, -x, 0), d->radiusX, d->radiusY);
//    painter->restore();
//}

//void HColorProgressBar::drarBarSplitLine(QPainter *painter)
//{
//    Q_D(HColorProgressBar);
//    if (!isShowBarSplitLine())
//        return;
//    auto s = barSplitLineStep() + painter->pen().width();
//    painter->save();
//    painter->setPen(barSplitLineColor());
//    for(int i = 0; i < d->barRect.right(); i += s)
//        painter->drawLine(i, 0, i, height());
//    painter->restore();
//}

//void HColorProgressBar::drawText(QPainter *painter)
//{
//    Q_D(HColorProgressBar);
//    auto p = 100.0 * toRatio(d->value);
//    auto t = QString("%1%").arg(QString::number(p, 'f', decimal()));
//    painter->save();
//    painter->setPen(palette().text().color());
//    painter->drawText(d->textRect, Qt::AlignCenter, t);
//    painter->restore();
//}

HE_END_NAMESPACE
