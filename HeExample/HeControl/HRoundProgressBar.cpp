#include "HRoundProgressBar_p.h"
#include <QtGui/QPainter>

HE_CONTROL_BEGIN_NAMESPACE

HRoundProgressBar::HRoundProgressBar(QWidget *parent) :
    HAbstractProgress(*new HRoundProgressBarPrivate, parent)
{
    setDataColors(QGradientStops() << QGradientStop(0, Qt::red) << QGradientStop(1, Qt::yellow));
}

HRoundProgressBar::HRoundProgressBar(HRoundProgressBarPrivate &p, QWidget *parent) :
    HAbstractProgress(p, parent)
{
}

HRoundProgressBar::~HRoundProgressBar()
{
}

HRoundProgressBar::BarStyle HRoundProgressBar::barStyle() const
{
    Q_D(const HRoundProgressBar);
    return d->barStyle;
}

bool HRoundProgressBar::isReverse() const
{
    Q_D(const HRoundProgressBar);
    return d->reverse;
}

int HRoundProgressBar::angleStart() const
{
    Q_D(const HRoundProgressBar);
    return d->angleStart;
}

bool HRoundProgressBar::isDrawExcircle() const
{
    Q_D(const HRoundProgressBar);
    return d->drawExcircle;
}

bool HRoundProgressBar::isDrawDataCircle() const
{
    Q_D(const HRoundProgressBar);
    return d->drawDataCircle;
}

bool HRoundProgressBar::isDrawInnerCircle() const
{
    Q_D(const HRoundProgressBar);
    return d->drawInnerCircle;
}

bool HRoundProgressBar::isDrawText() const
{
    Q_D(const HRoundProgressBar);
    return d->drawText;
}

QString HRoundProgressBar::format() const
{
    Q_D(const HRoundProgressBar);
    return d->format;
}

double HRoundProgressBar::excircleWidth() const
{
    Q_D(const HRoundProgressBar);
    return d->excircleWidth;
}

double HRoundProgressBar::dataCircleWidth() const
{
    Q_D(const HRoundProgressBar);
    return d->dataCircleWidth;
}

void HRoundProgressBar::setBarStyle(BarStyle value)
{
    Q_D(HRoundProgressBar);
    if (d->barStyle == value)
        return;
    d->barStyle = value;
    update();
}

void HRoundProgressBar::setReverse(bool b)
{
    Q_D(HRoundProgressBar);
    if (d->reverse == b)
        return;
    d->reverse = b;
    update();
}

void HRoundProgressBar::setAngleStart(int value)
{
    Q_D(HRoundProgressBar);
    if (d->angleStart == value)
        return;
    d->angleStart = value;
    update();
}

void HRoundProgressBar::setDrawExcircle(bool b)
{
    Q_D(HRoundProgressBar);
    if (d->drawExcircle == b)
        return;
    d->drawExcircle = b;
    update();
}

void HRoundProgressBar::setDrawDataCircle(bool b)
{
    Q_D(HRoundProgressBar);
    if (d->drawDataCircle == b)
        return;
    d->drawDataCircle = b;
    update();
}

void HRoundProgressBar::setDrawInnerCircle(bool b)
{
    Q_D(HRoundProgressBar);
    if (d->drawInnerCircle == b)
        return;
    d->drawInnerCircle = b;
    update();
}

void HRoundProgressBar::setDrawText(bool b)
{
    Q_D(HRoundProgressBar);
    if (d->drawText == b)
        return;
    d->drawText = b;
    update();
}

void HRoundProgressBar::setFormat(QString value)
{
    Q_D(HRoundProgressBar);
    if (d->format == value)
        return;
    d->format = value;
    update();
}

void HRoundProgressBar::setExcircleWidth(double value)
{
    Q_D(HRoundProgressBar);
    if (qFuzzyCompare(d->excircleWidth, value))
        return;
    d->excircleWidth = value;
    update();
}

void HRoundProgressBar::setDataCircleWidth(double value)
{
    Q_D(HRoundProgressBar);
    if (qFuzzyCompare(d->dataCircleWidth, value))
        return;
    d->dataCircleWidth = value;
    update();
}

void HRoundProgressBar::setDataColors(const QGradientStops &value)
{
    Q_D(HRoundProgressBar);
    if (d->gradientData == value)
        return;
    d->gradientData = value;
    d->rebuildBrush = true;
    update();
}

void HRoundProgressBar::paintEvent(QPaintEvent *)
{
    Q_D(HRoundProgressBar);

    d->outerRadius = qMin(width(), height());
    QPainter painter(this);
    painter.translate((width() - d->outerRadius) / 2, (height() - d->outerRadius) / 2);
    painter.drawImage(0, 0, createImage());
}

QImage HRoundProgressBar::createImage()
{
    Q_D(HRoundProgressBar);
    rebuildDataBrushIfNeeded();
    auto image = QImage(d->outerRadius, d->outerRadius, QImage::Format_ARGB32_Premultiplied);
    d->outerRect = QRectF(1, 1, d->outerRadius - 2, d->outerRadius - 2);
    d->innerRadius = d->barStyle == BarStyle_Line ? d->outerRadius - d->excircleWidth : d->outerRadius * 0.75;
    d->innerRect = QRectF((d->outerRadius - d->innerRadius) / 2, (d->outerRadius - d->innerRadius) / 2, d->innerRadius, d->innerRadius);

    QPainter painter(&image);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.fillRect(image.rect(), palette().background());
    drawExcircle(&painter);
    drawDataCircle(&painter);
    drawInnerCircle(&painter);
    drawText(&painter);
    return image;
}

void HRoundProgressBar::drawExcircle(QPainter *painter)
{
    Q_D(HRoundProgressBar);
    if (!d->drawExcircle)
        return;

    auto pen = QPen(d->barStyle == BarStyle_Donut ? palette().shadow().color() : palette().base().color(), d->excircleWidth);
    auto brush = QBrush(d->barStyle == BarStyle_Line ? Qt::NoBrush : palette().base());
    auto rect = d->barStyle == BarStyle_Line ? d->outerRect.adjusted(d->excircleWidth / 2, d->excircleWidth / 2, -d->excircleWidth / 2, -d->excircleWidth / 2) : d->outerRect;

    painter->save();
    painter->setPen(pen);
    painter->setBrush(brush);
    painter->drawEllipse(rect);
    painter->restore();
}

void HRoundProgressBar::drawDataCircle(QPainter *painter)
{
    Q_D(HRoundProgressBar);
    if (!d->drawDataCircle || qFuzzyCompare(d->value, d->minimum))
        return;

    auto span = (d->reverse ? -1 : 1) * 360 * toRatio(d->value);
    painter->save();
    if (d->barStyle == BarStyle_Line)
    {
        auto rect = d->outerRect.adjusted(d->excircleWidth / 2, d->excircleWidth / 2, -d->excircleWidth / 2, -d->excircleWidth / 2);
        painter->setPen(QPen(palette().highlight().color(), d->dataCircleWidth));
        painter->setBrush(Qt::NoBrush);
        if (qFuzzyCompare(d->value, d->maximum))
            painter->drawEllipse(rect);
        else
            painter->drawArc(rect, d->angleStart * 16, span * 16);
    }
    else
    {
        QPainterPath path;
        path.setFillRule(Qt::WindingFill);
        if (qFuzzyCompare(d->value, d->maximum))
        {
            path.addEllipse(d->outerRect);
        }
        else
        {
            path.moveTo(d->outerRect.center());
            path.arcTo(d->outerRect, d->angleStart, span);
            path.lineTo(d->outerRect.center());
        }
        painter->setPen(QPen(palette().shadow().color(), d->dataCircleWidth));
        painter->setBrush(palette().highlight());
        painter->drawPath(path);
    }
    painter->restore();
}

void HRoundProgressBar::drawInnerCircle(QPainter *painter)
{
    Q_D(HRoundProgressBar);
    if (!d->drawInnerCircle || d->barStyle != BarStyle_Donut)
        return;
    painter->save();
    painter->setBrush(palette().alternateBase());
    painter->drawEllipse(d->innerRect);
    painter->restore();
}

void HRoundProgressBar::drawText(QPainter *painter)
{
    Q_D(HRoundProgressBar);
    if (!d->drawText || d->format.isEmpty())
        return;

    auto f = font();
    f.setPointSize(10);
    auto fm = QFontMetricsF(f);
    auto width = fm.width(valueToText(d->maximum));
    f.setPointSizeF(f.pointSize() * 0.75 * d->innerRadius / width);

    painter->save();
    painter->setFont(f);
    painter->setPen(palette().text().color());
    painter->drawText(d->innerRect, Qt::AlignCenter, valueToText(d->value));
    painter->restore();
}

void HRoundProgressBar::rebuildDataBrushIfNeeded()
{
    Q_D(HRoundProgressBar);
    if (!d->rebuildBrush || d->gradientData.isEmpty() || d->barStyle == BarStyle_Line)
        return;
    d->rebuildBrush = false;

    auto p = palette();
    auto gradient = QConicalGradient(QPointF(0.5, 0.5), d->angleStart);
    gradient.setCoordinateMode(QGradient::StretchToDeviceMode);
    for (auto g : d->gradientData)
        gradient.setColorAt(1.0 - g.first, g.second);
    p.setBrush(QPalette::Highlight, gradient);
    setPalette(p);
}

QString HRoundProgressBar::valueToText(double value)
{
    Q_D(HRoundProgressBar);
    QString text = d->format;
    text.replace("%v", QString::number(value, 'f', d->decimal));
    text.replace("%p", QString::number(100 * toRatio(value), 'f', d->decimal));
    text.replace("%m", QString::number(range() + 1, 'f', d->decimal));
    return text;
}

HE_CONTROL_END_NAMESPACE
