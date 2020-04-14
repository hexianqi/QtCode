#include "HPanelItem_p.h"
#include <QtCore/QTimer>
#include <QtGui/QPainter>

HE_CONTROL_BEGIN_NAMESPACE

HPanelItem::HPanelItem(QWidget *parent) :
    QWidget(parent),
    d_ptr(new HPanelItemPrivate)
{
    init();
}

HPanelItem::HPanelItem(HPanelItemPrivate &p, QWidget *parent) :
    QWidget(parent),
    d_ptr(&p)
{
    init();
}

HPanelItem::~HPanelItem() = default;

int HPanelItem::borderWidth() const
{
    return d_ptr->borderWidth;
}

int HPanelItem::borderRadius() const
{
    return d_ptr->borderRadius;
}

QColor HPanelItem::borderColor() const
{
    return d_ptr->borderColor;
}

QColor HPanelItem::borderDisableColor() const
{
    return d_ptr->borderDisableColor;
}

int HPanelItem::titleHeight() const
{
    return d_ptr->titleHeight;
}

QString HPanelItem::titleText() const
{
    return d_ptr->titleText;
}

QFont HPanelItem::titleFont() const
{
    return d_ptr->titleFont;
}

Qt::Alignment HPanelItem::titleAlignment() const
{
    return d_ptr->titleAlignment;
}

QColor HPanelItem::titleColor() const
{
    return d_ptr->titleColor;
}

QColor HPanelItem::titleDisableColor() const
{
    return d_ptr->titleDisableColor;
}

bool HPanelItem::isAlarm() const
{
    return d_ptr->alarm;
}

int HPanelItem::alarmInterval() const
{
    return d_ptr->timer->interval();
}

QColor HPanelItem::alarmTextColor() const
{
    return d_ptr->alarmTextColor;
}

QColor HPanelItem::alarmDarkColor() const
{
    return d_ptr->alarmDarkColor;
}

QColor HPanelItem::alarmNormalColor() const
{
    return d_ptr->alarmNormalColor;
}

void HPanelItem::setBorderWidth(int value)
{
    if (d_ptr->borderWidth == value)
        return;
    d_ptr->borderWidth = value;
    update();
}

void HPanelItem::setBorderRadius(int value)
{
    if (d_ptr->borderRadius == value)
        return;
    d_ptr->borderRadius = value;
    update();
}

void HPanelItem::setBorderColor(const QColor &value)
{
    if (d_ptr->borderColor == value)
        return;
    d_ptr->borderColor = value;
    update();
}

void HPanelItem::setBorderDisableColor(const QColor &value)
{
    if (d_ptr->borderDisableColor == value)
        return;
    d_ptr->borderDisableColor = value;
    update();
}

void HPanelItem::setTitleHeight(int value)
{
    if (d_ptr->titleHeight == value)
        return;
    d_ptr->titleHeight = value;
    update();
}

void HPanelItem::setTitleText(const QString &value)
{
    if (d_ptr->titleText == value)
        return;
    d_ptr->titleText = value;
    update();
}

void HPanelItem::setTitleFont(const QFont &value)
{
    if (d_ptr->titleFont == value)
        return;
    d_ptr->titleFont = value;
    update();
}

void HPanelItem::setTitleAlignment(Qt::Alignment value)
{
    if (d_ptr->titleAlignment == value)
        return;
    d_ptr->titleAlignment = value;
    update();
}

void HPanelItem::setTitleColor(const QColor &value)
{
    if (d_ptr->titleColor == value)
        return;
    d_ptr->titleColor = value;
    update();
}

void HPanelItem::setTitleDisableColor(const QColor &value)
{
    if (d_ptr->titleDisableColor == value)
        return;
    d_ptr->titleDisableColor = value;
    update();
}

void HPanelItem::setAlarm(bool b)
{
    if (d_ptr->alarm == b)
        return;
    d_ptr->alarm = b;
    if (b)
        d_ptr->timer->start();
    else
        d_ptr->timer->stop();
}

void HPanelItem::setAlarmInterval(int value)
{
    if (d_ptr->timer->interval() == value)
        return;
    d_ptr->timer->setInterval(value);
}

void HPanelItem::setAlarmTextColor(const QColor &value)
{
    if (d_ptr->alarmTextColor == value)
        return;
    d_ptr->alarmTextColor = value;
    update();
}

void HPanelItem::setAlarmDarkColor(const QColor &value)
{
    if (d_ptr->alarmDarkColor == value)
        return;
    d_ptr->alarmDarkColor = value;
    update();
}

void HPanelItem::setAlarmNormalColor(const QColor &value)
{
    if (d_ptr->alarmNormalColor == value)
        return;
    d_ptr->alarmNormalColor = value;
    update();
}

void HPanelItem::paintEvent(QPaintEvent *)
{
    //绘制准备工作,启用反锯齿
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    //绘制边框
    drawBorder(&painter);
    //绘制标题
    drawTitle(&painter);
}

void HPanelItem::drawBorder(QPainter *painter)
{
    if (d_ptr->borderWidth <= 0)
        return;

    painter->save();
    painter->setPen(QPen(currentBorderColor(), d_ptr->borderWidth));
    painter->setBrush(Qt::NoBrush);
    painter->drawRoundedRect(d_ptr->borderWidth / 2, d_ptr->borderWidth / 2, width() - d_ptr->borderWidth, height() - d_ptr->borderWidth, d_ptr->borderRadius, d_ptr->borderRadius);
    painter->restore();
}

void HPanelItem::drawTitle(QPainter *painter)
{
    auto offset = d_ptr->borderWidth * 2 / 3;
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(currentBorderColor());
    painter->drawRect(offset, offset, width() - offset * 2, d_ptr->titleHeight);

    offset = d_ptr->borderWidth * 3;
    painter->setPen(currentTitleColor());
    painter->setFont(d_ptr->titleFont);
    painter->drawText(offset, 0, width() - offset * 2, d_ptr->titleHeight, QFlag(d_ptr->titleAlignment), d_ptr->titleText);
    painter->restore();
}

QColor HPanelItem::currentBorderColor()
{
    if (!isEnabled())
        return d_ptr->borderDisableColor;
    if (!isAlarm())
        return d_ptr->borderColor;
    if (!d_ptr->dark)
        return d_ptr->alarmNormalColor;
    return d_ptr->alarmDarkColor;
}

QColor HPanelItem::currentTitleColor()
{
    if (!isEnabled())
        return d_ptr->titleDisableColor;
    if (!isAlarm())
        return d_ptr->titleColor;
    return d_ptr->alarmTextColor;
}

void HPanelItem::init()
{
    d_ptr->titleFont = font();
    d_ptr->titleFont.setPointSize(15);
    d_ptr->timer = new QTimer(this);
    connect(d_ptr->timer, &QTimer::timeout, this, [=] { d_ptr->dark = !d_ptr->dark; update(); });
}

HE_CONTROL_END_NAMESPACE
