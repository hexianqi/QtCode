#include "HPercentGauge_p.h"
#include <QtGui/QPainter>
#include <QtCore/QtMath>

HE_CONTROL_BEGIN_NAMESPACE

HPercentGauge::HPercentGauge(QWidget *parent) :
    HAnimationProgress(*new HPercentGaugePrivate, parent)
{
}

HPercentGauge::HPercentGauge(HPercentGaugePrivate &p, QWidget *parent) :
    HAnimationProgress(p, parent)
{
}

HPercentGauge::~HPercentGauge()
{
}

QSize HPercentGauge::sizeHint() const
{
    return QSize(200, 200);
}

QSize HPercentGauge::minimumSizeHint() const
{
    return QSize(40, 40);
}

int HPercentGauge::scaleMajor() const
{
    Q_D(const HPercentGauge);
    return d->scaleMajor;
}

int HPercentGauge::scaleMinor() const
{
    Q_D(const HPercentGauge);
    return d->scaleMinor;
}

int HPercentGauge::angleStart() const
{
    Q_D(const HPercentGauge);
    return d->angleStart;
}

int HPercentGauge::angleEnd() const
{
    Q_D(const HPercentGauge);
    return d->angleEnd;
}

QColor HPercentGauge::background() const
{
    Q_D(const HPercentGauge);
    return d->background;
}

QColor HPercentGauge::baseColor() const
{
    Q_D(const HPercentGauge);
    return d->baseColor;
}

QColor HPercentGauge::arcColor() const
{
    Q_D(const HPercentGauge);
    return d->arcColor;
}

QColor HPercentGauge::scaleColor() const
{
    Q_D(const HPercentGauge);
    return d->scaleColor;
}

QColor HPercentGauge::scaleLabelColor() const
{
    Q_D(const HPercentGauge);
    return d->scaleLabelColor;
}

QColor HPercentGauge::textColor() const
{
    Q_D(const HPercentGauge);
    return d->textColor;
}

QColor HPercentGauge::titleColor() const
{
    Q_D(const HPercentGauge);
    return d->titleColor;
}

QString HPercentGauge::title() const
{
    Q_D(const HPercentGauge);
    return d->title;
}

void HPercentGauge::setDecimal(int value)
{
    if (value > 3)
        return;
    HAbstractProgress::setDecimal(value);
}

void HPercentGauge::setScaleMajor(int value)
{
    Q_D(HPercentGauge);
    if (d->scaleMajor == value)
        return;
    d->scaleMajor = value;
    update();
}

void HPercentGauge::setScaleMinor(int value)
{
    Q_D(HPercentGauge);
    if (d->scaleMinor == value)
        return;
    d->scaleMinor = value;
    update();
}

void HPercentGauge::setAngleStart(int value)
{
    Q_D(HPercentGauge);
    if (d->angleStart == value)
        return;
    d->angleStart = value;
    update();
}

void HPercentGauge::setAngleEnd(int value)
{
    Q_D(HPercentGauge);
    if (d->angleEnd == value)
        return;
    d->angleEnd = value;
    update();
}

void HPercentGauge::setBackground(const QColor &value)
{
    Q_D(HPercentGauge);
    if (d->background == value)
        return;
    d->background = value;
    update();
}

void HPercentGauge::setBaseColor(const QColor &value)
{
    Q_D(HPercentGauge);
    if (d->baseColor == value)
        return;
    d->baseColor = value;
    d->arcColor = d->baseColor;
    d->titleColor = d->baseColor;
    d->textColor = d->baseColor;
    d->baseColor.setAlpha(100);
    d->scaleColor = d->baseColor;
    d->baseColor.setAlpha(200);
    d->scaleLabelColor = d->baseColor;
    d->baseColor = value;
    update();
}

void HPercentGauge::setArcColor(const QColor &value)
{
    Q_D(HPercentGauge);
    if (d->arcColor == value)
        return;
    d->arcColor = value;
    update();
}

void HPercentGauge::setScaleColor(const QColor &value)
{
    Q_D(HPercentGauge);
    if (d->scaleColor == value)
        return;
    d->scaleColor = value;
    update();
}

void HPercentGauge::setScaleLabelColor(const QColor &value)
{
    Q_D(HPercentGauge);
    if (d->scaleLabelColor == value)
        return;
    d->scaleLabelColor = value;
    update();
}

void HPercentGauge::setTextColor(const QColor &value)
{
    Q_D(HPercentGauge);
    if (d->textColor == value)
        return;
    d->textColor = value;
    update();
}

void HPercentGauge::setTitleColor(const QColor &value)
{
    Q_D(HPercentGauge);
    if (d->titleColor == value)
        return;
    d->titleColor = value;
    update();
}

void HPercentGauge::setTitle(const QString &value)
{
    Q_D(HPercentGauge);
    if (d->title == value)
        return;
    d->title = value;
    update();
}

void HPercentGauge::paintEvent(QPaintEvent *)
{
    auto side = qMin(width(), height());
    QPainter painter(this);
    // 绘制准备工作,启用反锯齿,平移坐标轴中心,等比例缩放
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    painter.translate(width() / 2, height() / 2);
    painter.scale(side / 200.0, side / 200.0);
    // 绘制背景
    drawBackground(&painter);
    // 绘制圆弧
    drawArc(&painter);
    // 绘制圆弧进度小球
    drawCircle(&painter);
    // 绘制刻度线
    drawScale(&painter);
    // 绘制刻度值
    drawScaleLabel(&painter);
    // 绘制当前值
    drawValue(&painter);
    // 绘制标题
    drawTitle(&painter);
}

void HPercentGauge::drawBackground(QPainter *painter)
{
    Q_D(HPercentGauge);
    if (d->background == Qt::transparent)
        return;
    auto radius = 99;
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->fillRect(-radius, -radius, radius * 2, radius * 2, d->background);
    painter->restore();
}

void HPercentGauge::drawArc(QPainter *painter)
{
    Q_D(HPercentGauge);
    auto radius = 95;
    auto rect = QRectF(-radius, -radius, radius * 2, radius * 2);
    auto current = static_cast<int>(toAngle(d->currentValue));
    auto other = static_cast<int>(toAngle(d->maximum - d->currentValue));
    painter->save();
    painter->setBrush(Qt::NoBrush);
    painter->setPen(QPen(d->arcColor, 5, Qt::SolidLine, Qt::RoundCap));
    painter->drawArc(rect, (270 - d->angleStart - current) * 16, current * 16);
    painter->setPen(QPen(d->scaleColor, 5, Qt::SolidLine, Qt::RoundCap));
    painter->drawArc(rect, (270 - d->angleStart - current - other) * 16, other * 16);
    painter->restore();
}

void HPercentGauge::drawCircle(QPainter *painter)
{
    Q_D(HPercentGauge);
    auto radius = 5;
    auto offset = 85;
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(d->arcColor);
    painter->rotate(d->angleStart);
    painter->rotate(toAngle(d->currentValue));
    painter->drawEllipse(-radius, radius + offset, radius * 2, radius * 2);
    painter->restore();
}

void HPercentGauge::drawScale(QPainter *painter)
{
    Q_D(HPercentGauge);
    auto radius = 90;
    auto steps = d->scaleMajor * d->scaleMinor;
    auto angle = angleSpan() / steps;
    auto pen1 = QPen(d->scaleColor, 1.5, Qt::SolidLine, Qt::RoundCap);
    auto pen2 = QPen(d->scaleColor, 1, Qt::SolidLine, Qt::RoundCap);
    painter->save();
    painter->rotate(d->angleStart);
    for (int i = 0; i <= steps; i++)
    {
        if (i % d->scaleMinor == 0)
        {
            painter->setPen(pen1);
            painter->drawLine(0, radius - 10, 0, radius);
        }
        else
        {
            painter->setPen(pen2);
            painter->drawLine(0, radius - 5, 0, radius);
        }
        painter->rotate(angle);
    }
    painter->restore();
}

void HPercentGauge::drawScaleLabel(QPainter *painter)
{
    Q_D(HPercentGauge);
    auto radius = 70;
    auto start = qDegreesToRadians(270.0 - d->angleStart);
    auto delta = qDegreesToRadians(angleSpan()) / d->scaleMajor;
    painter->save();
    painter->setPen(d->scaleLabelColor);
    for (int i = 0; i <= d->scaleMajor; i++)
    {
        auto angle = start - i * delta;
        auto value = fromRatio(1.0 * i / d->scaleMajor);
        auto text = QString::number(value, 'f', d->decimal);
        auto textWidth = fontMetrics().width(text);
        auto textHeight = fontMetrics().height();
        auto x = radius * qCos(angle) - textWidth / 2;
        auto y = -radius * qSin(angle) + textHeight / 4;
        painter->drawText(QPointF(x, y), text);
    }
    painter->restore();
}

void HPercentGauge::drawValue(QPainter *painter)
{
    Q_D(HPercentGauge);
    auto radius = 100;
    auto f = font();
    f.setPixelSize(30);
    auto rect = QRectF(-radius, radius / 2, radius * 2, radius / 3);
    auto text = QString::number(d->currentValue, 'f', d->decimal);
    painter->save();
    painter->setPen(d->textColor);
    painter->setFont(f);
    painter->drawText(rect, Qt::AlignCenter, text);
    painter->restore();
}

void HPercentGauge::drawTitle(QPainter *painter)
{
    Q_D(HPercentGauge);
    if (d->title.isEmpty())
        return;
    auto radius = 100;
    auto f = font();
    f.setPixelSize(20);
    auto rect = QRectF(-radius, radius / 3, radius * 2, radius / 3);
    painter->save();
    painter->setPen(d->titleColor);
    painter->setFont(f);
    painter->drawText(rect, Qt::AlignCenter, d->title);
    painter->restore();
}

double HPercentGauge::angleSpan()
{
    Q_D(HPercentGauge);
    return 360.0 - d->angleStart - d->angleEnd;
}

double HPercentGauge::toAngle(double value)
{
    return angleSpan() * toRatio(value);
}

HE_CONTROL_END_NAMESPACE

