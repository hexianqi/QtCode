#include "HWeatherGauge_p.h"
#include "HXmlHelper.h"
#include <QtCore/QFile>
#include <QtCore/QPropertyAnimation>
#include <QtGui/QPainter>
#include <QtXml/QDomDocument>
#include <QtSvg/QSvgRenderer>

HE_CONTROL_BEGIN_NAMESPACE

HWeatherGaugePrivate::HWeatherGaugePrivate()
{
    minimum = -50;
    maximum = 50;
    angleEnd = 135;
    background = QColor(250, 250, 250);
    scaleMajor = 4;
    scaleMinor = 0;
}

HWeatherGauge::HWeatherGauge(QWidget *parent) :
    HCircleGauge(*new HWeatherGaugePrivate, parent)
{
    init();
}

HWeatherGauge::HWeatherGauge(HWeatherGaugePrivate &p, QWidget *parent) :
    HCircleGauge(p, parent)
{
    init();
}

HWeatherGauge::WeatherType HWeatherGauge::weatherType() const
{
    Q_D(const HWeatherGauge);
    return d->weatherType;
}

QColor HWeatherGauge::negativeColor() const
{
    Q_D(const HWeatherGauge);
    return d->negativeColor;
}

QColor HWeatherGauge::positiveColor() const
{
    Q_D(const HWeatherGauge);
    return d->positiveColor;
}

QColor HWeatherGauge::negativeTextColor() const
{
    Q_D(const HWeatherGauge);
    return d->negativeTextColor;
}

QColor HWeatherGauge::positiveTextColor() const
{
    Q_D(const HWeatherGauge);
    return d->positiveTextColor;
}

QColor HWeatherGauge::negativePixmapColor() const
{
    Q_D(const HWeatherGauge);
    return d->negativePixmapColor;
}

QColor HWeatherGauge::positivePixmapColor() const
{
    Q_D(const HWeatherGauge);
    return d->positivePixmapColor;
}

double HWeatherGauge::outerValue() const
{
    Q_D(const HWeatherGauge);
    return d->outerValue;
}

double HWeatherGauge::outerMinimum() const
{
    Q_D(const HWeatherGauge);
    return d->outerMinimum;
}

double HWeatherGauge::outerMaximum() const
{
    Q_D(const HWeatherGauge);
    return d->outerMaximum;
}

int HWeatherGauge::outerAngleStart() const
{
    Q_D(const HWeatherGauge);
    return d->outerAngleStart;
}

int HWeatherGauge::outerAngleEnd() const
{
    Q_D(const HWeatherGauge);
    return d->outerAngleEnd;
}

QColor HWeatherGauge::outerRingBackground() const
{
    Q_D(const HWeatherGauge);
    return d->outerRingBackground;
}

QColor HWeatherGauge::outerRingColor() const
{
    Q_D(const HWeatherGauge);
    return d->outerRingColor;
}

QColor HWeatherGauge::outerTextColor() const
{
    Q_D(const HWeatherGauge);
    return d->outerTextColor;
}

void HWeatherGauge::setWeatherType(WeatherType value)
{
    Q_D(HWeatherGauge);
    if (d->weatherType == value)
        return;
    d->weatherType = value;
    update();
}

void HWeatherGauge::setNegativeColor(const QColor &value)
{
    Q_D(HWeatherGauge);
    if (d->negativeColor == value)
        return;
    d->negativeColor = value;
    update();
}

void HWeatherGauge::setPositiveColor(const QColor &value)
{
    Q_D(HWeatherGauge);
    if (d->positiveColor == value)
        return;
    d->positiveColor = value;
    update();
}

void HWeatherGauge::setNegativeTextColor(const QColor &value)
{
    Q_D(HWeatherGauge);
    if (d->negativeTextColor == value)
        return;
    d->negativeTextColor = value;
    update();
}

void HWeatherGauge::setPositiveTextColor(const QColor &value)
{
    Q_D(HWeatherGauge);
    if (d->positiveTextColor == value)
        return;
    d->positiveTextColor = value;
    update();
}

void HWeatherGauge::setNegativePixmapColor(const QColor &value)
{
    Q_D(HWeatherGauge);
    if (d->negativePixmapColor == value)
        return;
    d->negativePixmapColor = value;
    update();
}

void HWeatherGauge::setPositivePixmapColor(const QColor &value)
{
    Q_D(HWeatherGauge);
    if (d->positivePixmapColor == value)
        return;
    d->positivePixmapColor = value;
    update();
}

void HWeatherGauge::setOuterRange(double minimum, double maximum)
{
    Q_D(HWeatherGauge);
    if (minimum >= maximum)
        qSwap(minimum, maximum);

    d->outerMinimum = minimum;
    d->outerMaximum = maximum;
    if (d->outerValue < minimum || d->outerValue > maximum)
        setValue(qBound(minimum, d->outerValue, maximum));
    else
        update();
}

void HWeatherGauge::setOuterValue(double value)
{
    Q_D(HWeatherGauge);
    if (value < d->outerMinimum || value > d->outerMinimum || qFuzzyCompare(value, d->outerValue))
        return;
    d->outerValue = value;
    if (d->animationEnable)
    {
        d->outerAnimation->setStartValue(d->outerCurrentValue);
        d->outerAnimation->setEndValue(value);
        d->outerAnimation->start();
    }
    else
    {
        d->outerCurrentValue = value;
        update();
    }
}

void HWeatherGauge::setOuterMinimum(double value)
{
    Q_D(HWeatherGauge);
    setOuterRange(value, d->outerMaximum);
}

void HWeatherGauge::setOuterMaximum(double value)
{
    Q_D(HWeatherGauge);
    setOuterRange(d->outerMinimum, value);
}

void HWeatherGauge::setOuterAngleStart(int value)
{
    Q_D(HWeatherGauge);
    if (d->outerAngleStart == value)
        return;
    d->outerAngleStart = value;
    update();
}

void HWeatherGauge::setOuterAngleEnd(int value)
{
    Q_D(HWeatherGauge);
    if (d->outerAngleEnd == value)
        return;
    d->outerAngleEnd = value;
    update();
}

void HWeatherGauge::setOuterRingBackground(const QColor &value)
{
    Q_D(HWeatherGauge);
    if (d->outerRingBackground == value)
        return;
    d->outerRingBackground = value;
    update();
}

void HWeatherGauge::setOuterRingColor(const QColor &value)
{
    Q_D(HWeatherGauge);
    if (d->outerRingColor == value)
        return;
    d->outerRingColor = value;
    update();
}

void HWeatherGauge::setOuterTextColor(const QColor &value)
{
    Q_D(HWeatherGauge);
    if (d->outerTextColor == value)
        return;
    d->outerTextColor = value;
    update();
}

void HWeatherGauge::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    preDraw(&painter);
    // 绘制进度条
    drawProgress(&painter, 100);
    // 绘制刻度线
    drawScale(&painter, 68);
    // 绘制刻度值
    drawScaleLabel(&painter, 50);
    //绘制中心图片
    drawPixmap(&painter);
    // 绘制当前值
    drawValue(&painter, 100);
}

void HWeatherGauge::drawProgress(QPainter *painter, int /*radius*/)
{
    Q_D(HWeatherGauge);
    auto penWidth = 13;
    auto radius1 = 92;
    auto radius2 = 77;
    auto rect1 = QRectF(-radius1, -radius1, radius1 * 2, radius1 * 2);
    auto rect2 = QRectF(-radius2, -radius2, radius2 * 2, radius2 * 2);
    auto span1 = 360 - d->outerAngleEnd - d->outerAngleStart;
    auto span2 = static_cast<int>(angleSpan());
    auto angle1 = static_cast<int>(span1 * ((d->outerCurrentValue - d->outerMinimum) / (d->outerMaximum - d->outerMinimum)));
    auto angle2 = static_cast<int>(toAngle(d->currentValue));
    auto angle0 = static_cast<int>(toAngle(0));

    painter->save();
    painter->setBrush(Qt::NoBrush);
    painter->setPen(QPen(d->outerRingBackground, penWidth, Qt::SolidLine, Qt::FlatCap, Qt::MPenJoinStyle));
    painter->drawArc(rect1, (270 - d->outerAngleStart - span1) * 16, span1 * 16);
    painter->setPen(QPen(d->outerRingColor, penWidth, Qt::SolidLine, Qt::FlatCap, Qt::MPenJoinStyle));
    painter->drawArc(rect1, (270 - d->outerAngleStart - angle1) * 16, angle1 * 16);
    painter->setPen(QPen(d->background, penWidth, Qt::SolidLine, Qt::FlatCap, Qt::MPenJoinStyle));
    painter->drawArc(rect2, (270 - d->angleStart - span2) * 16, span2 * 16);
    painter->setPen(QPen(d->currentValue >= 0 ? d->positiveColor : d->negativeColor, penWidth, Qt::SolidLine, Qt::FlatCap, Qt::MPenJoinStyle));
    painter->drawArc(rect2, (270 - d->angleStart - angle0) * 16, (angle0 - angle2) * 16);
    painter->restore();
}

void HWeatherGauge::drawValue(QPainter *painter, int /*radius*/)
{
    Q_D(HWeatherGauge);
    auto f = font();
    f.setPixelSize(20);
    auto rect1 = QRectF(2, -32, 50, 30);
    auto rect2 = QRectF(2,   2, 50, 30);
    auto text1 = QString("%1℃").arg(d->currentValue, 0, 'f', d->decimal);
    auto text2 = QString("%1F").arg(d->outerCurrentValue, 0, 'f', d->decimal);
    painter->save();
    painter->setFont(f);
    painter->setPen(d->currentValue >= 0 ? d->positiveTextColor : d->negativeTextColor);
    painter->drawText(rect1, Qt::AlignBottom | Qt::AlignLeft, text1);
    painter->setPen(d->outerCurrentValue >= 0 ? d->positiveTextColor : d->negativeTextColor);
    painter->drawText(rect2, Qt::AlignTop | Qt::AlignLeft, text2);
    painter->restore();
}

void HWeatherGauge::drawPixmap(QPainter *painter)
{
    Q_D(HWeatherGauge);
    auto fileName = d->svgPaths.value(d->weatherType);
    if (fileName.isEmpty())
        return;

    QFile file(fileName);
    file.open(QIODevice::ReadOnly);
    QDomDocument doc;
    doc.setContent(file.readAll());
    file.close();
    HXmlHelper::setAttribute(doc.documentElement(), "path", "fill", d->currentValue >= 0 ? d->positivePixmapColor.name() : d->negativePixmapColor.name());

    painter->save();
    auto svg = new QSvgRenderer(doc.toByteArray(), this);
    svg->render(painter ,QRectF(-40, -20, 40, 40));
    painter->restore();
}

void HWeatherGauge::init()
{
    Q_D(HWeatherGauge);
    d->svgPaths.insert(WeatherType_Sun,             ":/image/beautify/sun.svg");
    d->svgPaths.insert(WeatherType_Rain,            ":/image/beautify/rain.svg");
    d->svgPaths.insert(WeatherType_Snow,            ":/image/beautify/snow.svg");
    d->svgPaths.insert(WeatherType_Cloud,           ":/image/beautify/cloud.svg");
    d->svgPaths.insert(WeatherType_Wind,            ":/image/beautify/wind.svg");
    d->svgPaths.insert(WeatherType_SnowRain,        ":/image/beautify/rain_snow.svg");
    d->svgPaths.insert(WeatherType_Hail,            ":/image/beautify/hail.svg");
    d->svgPaths.insert(WeatherType_Thunderstorm,    ":/image/beautify/thunderstorm.svg");
    d->svgPaths.insert(WeatherType_Fog,             ":/image/beautify/fog.svg");
    d->svgPaths.insert(WeatherType_PartlyCloudy,    ":/image/beautify/partly_cloud.svg");

    d->outerAnimation = new QPropertyAnimation(this);
    d->outerAnimation->setTargetObject(this);
    d->outerAnimation->setEasingCurve(QEasingCurve::Linear);
    connect(d->outerAnimation, &QPropertyAnimation::valueChanged, this, [=](QVariant value) { setOuterValue(value.toDouble()); });
}

HE_CONTROL_END_NAMESPACE
