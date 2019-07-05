#include "HRingProgressBar_p.h"
#include <QtGui/QPainter>

HE_CONTROL_BEGIN_NAMESPACE

HRingProgressBar::HRingProgressBar(QWidget *parent) :
    HAnimationProgress(*new HRingProgressBarPrivate, parent)
{
}

HRingProgressBar::HRingProgressBar(HRingProgressBarPrivate &p, QWidget *parent) :
    HAnimationProgress(p, parent)
{
}

HRingProgressBar::~HRingProgressBar()
{
}

QSize HRingProgressBar::sizeHint() const
{
    return QSize(200, 200);
}

QSize HRingProgressBar::minimumSizeHint() const
{
    return QSize(40, 40);
}

bool HRingProgressBar::isReverse() const
{
    Q_D(const HRingProgressBar);
    return d->reverse;
}

bool HRingProgressBar::isShowPercent() const
{
    Q_D(const HRingProgressBar);
    return d->showPercent;
}

int HRingProgressBar::alarmMode() const
{
    Q_D(const HRingProgressBar);
    return d->alarmMode;
}

int HRingProgressBar::angleStart() const
{
    Q_D(const HRingProgressBar);
    return d->angleStart;
}

int HRingProgressBar::ringPadding() const
{
    Q_D(const HRingProgressBar);
    return d->ringPadding;
}

int HRingProgressBar::ringWidth() const
{
    Q_D(const HRingProgressBar);
    return d->ringWidth;
}

int HRingProgressBar::ringValue1() const
{
    Q_D(const HRingProgressBar);
    return d->ringValue1;
}

int HRingProgressBar::ringValue2() const
{
    Q_D(const HRingProgressBar);
    return d->ringValue2;
}

int HRingProgressBar::ringValue3() const
{
    Q_D(const HRingProgressBar);
    return d->ringValue3;
}

QColor HRingProgressBar::background() const
{
    Q_D(const HRingProgressBar);
    return d->background;
}

QColor HRingProgressBar::textColor() const
{
    Q_D(const HRingProgressBar);
    return d->textColor;
}

QColor HRingProgressBar::circleColor() const
{
    Q_D(const HRingProgressBar);
    return d->circleColor;
}

QColor HRingProgressBar::ringBackground() const
{
    Q_D(const HRingProgressBar);
    return d->ringBackground;
}

QColor HRingProgressBar::ringColor() const
{
    Q_D(const HRingProgressBar);
    return d->ringColor;
}

QColor HRingProgressBar::ringColor1() const
{
    Q_D(const HRingProgressBar);
    return d->ringColor1;
}

QColor HRingProgressBar::ringColor2() const
{
    Q_D(const HRingProgressBar);
    return d->ringColor2;
}

QColor HRingProgressBar::ringColor3() const
{
    Q_D(const HRingProgressBar);
    return d->ringColor3;
}

void HRingProgressBar::setDecimal(int value)
{
    if (value > 3)
        return;
    HAnimationProgress::setDecimal(value);
}

void HRingProgressBar::setReverse(bool b)
{
    Q_D(HRingProgressBar);
    if (d->reverse == b)
        return;
    d->reverse = b;
    update();
}

void HRingProgressBar::setShowPercent(bool b)
{
    Q_D(HRingProgressBar);
    if (d->showPercent == b)
        return;
    d->showPercent = b;
    update();
}

void HRingProgressBar::setAlarmMode(int value)
{
    Q_D(HRingProgressBar);
    if (d->alarmMode == value)
        return;
    d->alarmMode = value;
    update();
}

void HRingProgressBar::setAngleStart(int value)
{
    Q_D(HRingProgressBar);
    if (d->angleStart == value)
        return;
    d->angleStart = value;
    update();
}

void HRingProgressBar::setRingPadding(int value)
{
    Q_D(HRingProgressBar);
    if (d->ringPadding == value)
        return;
    d->ringPadding = value;
    update();
}

void HRingProgressBar::setRingWidth(int value)
{
    Q_D(HRingProgressBar);
    if (d->ringWidth == value)
        return;
    d->ringWidth = value;
    update();
}

void HRingProgressBar::setRingValue1(int value)
{
    Q_D(HRingProgressBar);
    if (d->ringValue1 == value)
        return;
    d->ringValue1 = value;
    update();
}

void HRingProgressBar::setRingValue2(int value)
{
    Q_D(HRingProgressBar);
    if (d->ringValue2 == value)
        return;
    d->ringValue2 = value;
    update();
}

void HRingProgressBar::setRingValue3(int value)
{
    Q_D(HRingProgressBar);
    if (d->ringValue3 == value)
        return;
    d->ringValue3 = value;
    update();
}

void HRingProgressBar::setBackground(const QColor &value)
{
    Q_D(HRingProgressBar);
    if (d->background == value)
        return;
    d->background = value;
    update();
}

void HRingProgressBar::setTextColor(const QColor &value)
{
    Q_D(HRingProgressBar);
    if (d->textColor == value)
        return;
    d->textColor = value;
    update();
}

void HRingProgressBar::setCircleColor(const QColor &value)
{
    Q_D(HRingProgressBar);
    if (d->circleColor == value)
        return;
    d->circleColor = value;
    update();
}

void HRingProgressBar::setRingBackground(const QColor &value)
{
    Q_D(HRingProgressBar);
    if (d->ringBackground == value)
        return;
    d->ringBackground = value;
    update();
}

void HRingProgressBar::setRingColor(const QColor &value)
{
    Q_D(HRingProgressBar);
    if (d->ringColor == value)
        return;
    d->ringColor = value;
    update();
}

void HRingProgressBar::setRingColor1(const QColor &value)
{
    Q_D(HRingProgressBar);
    if (d->ringColor1 == value)
        return;
    d->ringColor1 = value;
    update();
}

void HRingProgressBar::setRingColor2(const QColor &value)
{
    Q_D(HRingProgressBar);
    if (d->ringColor2 == value)
        return;
    d->ringColor2 = value;
    update();
}

void HRingProgressBar::setRingColor3(const QColor &value)
{
    Q_D(HRingProgressBar);
    if (d->ringColor3 == value)
        return;
    d->ringColor3 = value;
    update();
}

void HRingProgressBar::paintEvent(QPaintEvent *)
{
    auto side = qMin(width(), height());
    QPainter painter(this);
    // 绘制准备工作,启用反锯齿,平移坐标轴中心,等比例缩放
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    painter.translate(width() / 2, height() / 2);
    painter.scale(side / 200.0, side / 200.0);
    // 绘制背景
    drawBackground(&painter);
    // 绘制进度
    drawRing(&painter);
    // 绘制间隔,重新绘制一个圆遮住,产生间距效果
    drawPadding(&painter);
    //绘制中间圆
    drawCircle(&painter);
    //绘制当前值
    drawValue(&painter);
}

void HRingProgressBar::drawBackground(QPainter *painter)
{
    Q_D(HRingProgressBar);
    auto radius = 99;
    painter->save();
    painter->setPen(Qt::NoPen);
    // 这里有个技巧,如果没有间距则设置成圆环的背景色
    painter->setBrush(d->ringPadding == 0 ? d->ringBackground : d->background);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    painter->restore();
}

void HRingProgressBar::drawRing(QPainter *painter)
{
    Q_D(HRingProgressBar);
    auto radius = 99 - d->ringPadding;
    auto current = static_cast<int>((d->reverse ? -360 : 360) * toRatio(d->currentValue));
    auto other = static_cast<int>((d->reverse ? -360 : 360) * toRatio(d->maximum - d->currentValue));
    auto rect = QRectF(-radius, -radius, radius * 2, radius * 2);
    auto color = d->ringColor;
    // 动态设置当前进度颜色
    if (d->alarmMode == 1)
    {
        if (d->currentValue >= d->ringValue3)
            color = d->ringColor3;
        else if (d->currentValue >= d->ringValue2)
            color = d->ringColor2;
        else
            color = d->ringColor1;
    }
    else if (d->alarmMode == 2)
    {
        if (d->currentValue <= d->ringValue1)
            color = d->ringColor1;
        else if (d->currentValue <= d->ringValue2)
            color = d->ringColor2;
        else
            color = d->ringColor3;
    }
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(color);
    painter->drawPie(rect, (d->angleStart - current) * 16, current * 16);
    painter->setBrush(d->ringBackground);
    painter->drawPie(rect, (d->angleStart - current - other) * 16, other * 16);
    painter->restore();
}

void HRingProgressBar::drawPadding(QPainter *painter)
{
    Q_D(HRingProgressBar);
    if (d->ringPadding <= 0)
        return;
    auto radius = 99 - d->ringWidth - d->ringPadding;
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(d->background);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    painter->restore();
}

void HRingProgressBar::drawCircle(QPainter *painter)
{
    // 文字的区域要减去进度的宽度及间距
    Q_D(HRingProgressBar);
    auto radius = 99 - d->ringWidth - d->ringPadding * 2;
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(d->circleColor);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    painter->restore();
}

void HRingProgressBar::drawValue(QPainter *painter)
{
    // 文字的区域要减去进度的宽度及间距
    Q_D(HRingProgressBar);
    auto radius = 99 - d->ringWidth - d->ringPadding * 2;
    auto f = font();
    f.setPixelSize(radius - (d->showPercent ? 20 : 6));
    auto rect = QRectF(-radius, -radius, radius * 2, radius * 2);
    QString text;
    if (d->showPercent)
    {
        f.setPixelSize(radius - 20);
        text = QString("%1%").arg(100 * toRatio(d->currentValue), 0, 'f', d->decimal);
    }
    else
    {
        f.setPixelSize(radius - 6);
        text = QString("%1").arg(d->currentValue, 0, 'f', d->decimal);
    }
    painter->save();
    painter->setPen(d->textColor);
    painter->setFont(f);
    painter->drawText(rect, Qt::AlignCenter, text);
    painter->restore();
}

HE_CONTROL_END_NAMESPACE
