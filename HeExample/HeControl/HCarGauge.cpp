#include "HCarGauge_p.h"
#include "HDrawHelper.h"
#include <QtGui/QPainter>

HE_BEGIN_NAMESPACE

HCarGaugePrivate::HCarGaugePrivate()
{
    scaleMajor = 10;
    scaleMinor = 10;
    angleStart = 45;
    angleEnd = 45;
    scaleColor = QColor(255, 255, 255);
    scaleLabelColor = QColor(255, 255, 255);
    pointerColor = QColor(255, 107, 107);
    textColor = QColor(0, 0, 0);
}

HCarGauge::HCarGauge(QWidget *parent) :
    HCircleGauge(*new HCarGaugePrivate, parent)
{
}

HCarGauge::HCarGauge(HCarGaugePrivate &p, QWidget *parent) :
    HCircleGauge(p, parent)
{
}

QColor HCarGauge::outerCircleColor() const
{
    Q_D(const HCarGauge);
    return d->outerCircleColor;
}

QColor HCarGauge::innerCircleColor() const
{
    Q_D(const HCarGauge);
    return d->innerCircleColor;
}

QColor HCarGauge::coverCircleColor() const
{
    Q_D(const HCarGauge);
    return d->coverCircleColor;
}

QColor HCarGauge::centerCircleColor() const
{
    Q_D(const HCarGauge);
    return d->centerCircleColor;
}

QColor HCarGauge::pieColorStart() const
{
    Q_D(const HCarGauge);
    return d->pieColorStart;
}

QColor HCarGauge::pieColorMid() const
{
    Q_D(const HCarGauge);
    return d->pieColorMid;
}

QColor HCarGauge::pieColorEnd() const
{
    Q_D(const HCarGauge);
    return d->pieColorEnd;
}

bool HCarGauge::isShowOverlay() const
{
    Q_D(const HCarGauge);
    return d->showOverlay;
}

QColor HCarGauge::overlayColor() const
{
    Q_D(const HCarGauge);
    return d->overlayColor;
}

HCarGauge::PieStyle HCarGauge::pieStyle() const
{
    Q_D(const HCarGauge);
    return d->pieStyle;
}

HControlType::PointerStyle HCarGauge::pointerStyle() const
{
    Q_D(const HCarGauge);
    return d->pointerStyle;
}

void HCarGauge::setOuterCircleColor(const QColor &value)
{
    Q_D(HCarGauge);
    if (d->outerCircleColor == value)
        return;
    d->outerCircleColor = value;
    update();
}

void HCarGauge::setInnerCircleColor(const QColor &value)
{
    Q_D(HCarGauge);
    if (d->innerCircleColor == value)
        return;
    d->innerCircleColor = value;
    update();
}

void HCarGauge::setCoverCircleColor(const QColor &value)
{
    Q_D(HCarGauge);
    if (d->coverCircleColor == value)
        return;
    d->coverCircleColor = value;
    update();
}

void HCarGauge::setCenterCircleColor(const QColor &value)
{
    Q_D(HCarGauge);
    if (d->centerCircleColor == value)
        return;
    d->centerCircleColor = value;
    update();
}

void HCarGauge::setPieColorStart(const QColor &value)
{
    Q_D(HCarGauge);
    if (d->pieColorStart == value)
        return;
    d->pieColorStart = value;
    update();
}

void HCarGauge::setPieColorMid(const QColor &value)
{
    Q_D(HCarGauge);
    if (d->pieColorMid == value)
        return;
    d->pieColorMid = value;
    update();
}

void HCarGauge::setPieColorEnd(const QColor &value)
{
    Q_D(HCarGauge);
    if (d->pieColorEnd == value)
        return;
    d->pieColorEnd = value;
    update();
}

void HCarGauge::setShowOverlay(bool b)
{
    Q_D(HCarGauge);
    if (d->showOverlay == b)
        return;
    d->showOverlay = b;
    update();
}

void HCarGauge::setOverlayColor(const QColor &value)
{
    Q_D(HCarGauge);
    if (d->overlayColor == value)
        return;
    d->overlayColor = value;
    update();
}

void HCarGauge::setPieStyle(PieStyle value)
{
    Q_D(HCarGauge);
    if (d->pieStyle == value)
        return;
    d->pieStyle = value;
    update();
}

void HCarGauge::setPointerStyle(HControlType::PointerStyle value)
{
    Q_D(HCarGauge);
    if (d->pointerStyle == value)
        return;
    d->pointerStyle = value;
    update();
}

void HCarGauge::paintEvent(QPaintEvent *)
{
    Q_D(HCarGauge);
    QPainter painter(this);
    preDraw(&painter);
    // 绘制外圆
    drawOuterCircle(&painter);
    // 绘制内圆
    drawInnerCircle(&painter);
    // 绘制饼圆
    drawColorPie(&painter);
    // 绘制覆盖圆 用以遮住饼圆多余部分
    drawCoverCircle(&painter);
    // 绘制刻度线
    drawScale(&painter, 72);
    // 绘制刻度值
    drawScaleLabel(&painter, 82);
    // 绘制指示器
    drawPointer(&painter, 100);
    // 绘制中心圆
    drawCenterCircle(&painter);
    // 绘制当前值
    drawValue(&painter, 100);
    // 绘制遮罩层
    if (d->showOverlay)
        HDrawHelper::drawOverlay(&painter, 90, d->overlayColor);
}

void HCarGauge::drawProgress(QPainter *, int /*radius*/)
{

}

void HCarGauge::drawPointer(QPainter *painter, int /*radius*/)
{
    Q_D(HCarGauge);
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(d->pointerColor);
    painter->rotate(d->angleStart);
    painter->rotate(toAngle(d->currentValue));
    if (d->pointerStyle == HControlType::PointerStyle_Circle)
        drawPointerCircle(painter);
    if (d->pointerStyle == HControlType::PointerStyle_Indicator)
        drawPointerIndicator(painter);
    if (d->pointerStyle == HControlType::PointerStyle_IndicatorR)
        drawPointerIndicatorR(painter);
    if (d->pointerStyle == HControlType::PointerStyle_Triangle)
        drawPointerTriangle(painter);
    drawPointerCenter(painter);
    painter->restore();
}

void HCarGauge::drawValue(QPainter *painter, int radius)
{
    Q_D(HCarGauge);
    auto f = font();
    f.setPixelSize(18);
    auto rect = QRectF(-radius, -radius, radius * 2, radius * 2);
    auto text = QString::number(d->currentValue, 'f', d->decimal);
    painter->save();
    painter->setPen(d->textColor);
    painter->setFont(f);
    painter->drawText(rect, Qt::AlignCenter, text);
    painter->restore();
}

void HCarGauge::drawOuterCircle(QPainter *painter)
{
    Q_D(HCarGauge);
    auto radius = 99;
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(d->outerCircleColor);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    painter->restore();
}

void HCarGauge::drawInnerCircle(QPainter *painter)
{
    Q_D(HCarGauge);
    auto radius = 90;
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(d->innerCircleColor);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    painter->restore();
}

void HCarGauge::drawColorPie(QPainter *painter)
{
    Q_D(HCarGauge);
    auto radius = 60;
    auto rect = QRectF(-radius, -radius, radius * 2, radius * 2);
    painter->save();
    painter->setPen(Qt::NoPen);
    if (d->pieStyle == PieStyle_Three)
    {
        auto offset = 3;
        auto angleStart = static_cast<int>(angleSpan() * 0.7);
        auto angleMid = static_cast<int>(angleSpan() * 0.15);
        auto angleEnd = static_cast<int>(angleSpan() * 0.15);
        painter->setBrush(d->pieColorStart);
        painter->drawPie(rect, (270 - d->angleStart - angleStart) * 16, angleStart * 16);
        painter->setBrush(d->pieColorMid);
        painter->drawPie(rect, (270 - d->angleStart - angleStart - angleMid) * 16 + offset, angleMid * 16);
        painter->setBrush(d->pieColorEnd);
        painter->drawPie(rect, (270 - d->angleStart - angleStart - angleMid - angleEnd) * 16 + offset * 2, angleEnd * 16);
    }
    if (d->pieStyle == PieStyle_Current)
    {
        auto current = static_cast<int>(toAngle(d->currentValue));
        auto other = static_cast<int>(toAngle(d->maximum - d->currentValue));
        painter->setBrush(d->pieColorStart);
        painter->drawPie(rect, (270 - d->angleStart - current) * 16, current * 16);
        painter->setBrush(d->pieColorEnd);
        painter->drawPie(rect, (270 - d->angleStart - current - other) * 16, other * 16);
    }
    painter->restore();
}

void HCarGauge::drawCoverCircle(QPainter *painter)
{
    Q_D(HCarGauge);
    auto radius = 50;
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(d->coverCircleColor);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    painter->restore();
}

void HCarGauge::drawPointerCircle(QPainter *painter)
{
    auto radius = 6;
    auto offset = 30;
    painter->drawEllipse(-radius, radius + offset, radius * 2, radius * 2);
}

void HCarGauge::drawPointerIndicator(QPainter *painter)
{
    auto radius = 75;
    auto poly = QPolygon() << QPoint(-5, 0) << QPoint(5, 0) << QPoint(0, radius);
    painter->setOpacity(0.8);
    painter->drawConvexPolygon(poly);
}

void HCarGauge::drawPointerIndicatorR(QPainter *painter)
{
    Q_D(HCarGauge);
    auto radius = 75;
    auto poly = QPolygon() << QPoint(-5, 0) << QPoint(5, 0) << QPoint(0, radius);
    painter->setPen(QPen(d->pointerColor, 1));
    painter->drawConvexPolygon(poly);
    // 增加绘制圆角直线,与之前三角形重叠,形成圆角指针
    painter->setPen(QPen(d->pointerColor, 4, Qt::SolidLine, Qt::RoundCap));
    painter->drawLine(0, 0, 0, radius);
}

void HCarGauge::drawPointerTriangle(QPainter *painter)
{
    auto radius = 10;
    auto offset = 38;
    auto poly = QPolygon() << QPoint(-5, offset) << QPoint(5, offset) << QPoint(0, radius + offset);
    painter->drawConvexPolygon(poly);
}

void HCarGauge::drawPointerCenter(QPainter *painter)
{
    auto radius = 18;
    painter->setOpacity(0.8);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
}

void HCarGauge::drawCenterCircle(QPainter *painter)
{
    Q_D(HCarGauge);
    auto radius = 15;
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(d->centerCircleColor);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    painter->restore();
}

HE_END_NAMESPACE
