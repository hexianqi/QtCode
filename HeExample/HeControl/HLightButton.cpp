#include "HLightButton_p.h"
#include "HMoveEventFilter.h"
#include "HDrawHelper.h"
#include <QtCore/QTimer>
#include <QtGui/QPainter>

HE_CONTROL_BEGIN_NAMESPACE

HLightButton::HLightButton(QWidget *parent) :
    QWidget(parent),
    d_ptr(new HLightButtonPrivate)
{
    init();
}

HLightButton::HLightButton(HLightButtonPrivate &p, QWidget *parent) :
    QWidget(parent),
    d_ptr(&p)
{
    init();
}

HLightButton::~HLightButton()
{
    if (d_ptr->timer->isActive())
        d_ptr->timer->stop();
}

QSize HLightButton::sizeHint() const
{
    return QSize(100, 100);
}

QSize HLightButton::minimumSizeHint() const
{
    return QSize(10, 10);
}

QString HLightButton::text() const
{
    return d_ptr->text;
}

QColor HLightButton::textColor() const
{
    return d_ptr->textColor;
}

QColor HLightButton::alarmColor() const
{
    return d_ptr->alarmColor;
}

QColor HLightButton::normalColor() const
{
    return d_ptr->normalColor;
}

QColor HLightButton::borderOutColorStart() const
{
    return d_ptr->borderOutColorStart;
}

QColor HLightButton::borderOutColorEnd() const
{
    return d_ptr->borderOutColorEnd;
}

QColor HLightButton::borderInColorStart() const
{
    return d_ptr->borderInColorStart;
}

QColor HLightButton::borderInColorEnd() const
{
    return d_ptr->borderInColorEnd;
}

QColor HLightButton::background() const
{
    return d_ptr->background;
}

QColor HLightButton::overlayColor() const
{
    return d_ptr->overlayColor;
}

bool HLightButton::isMoveEnable() const
{
    return d_ptr->moveEnable;
}

bool HLightButton::isShowRect() const
{
    return d_ptr->showRect;
}

bool HLightButton::isShowOverlay() const
{
    return d_ptr->showOverlay;
}

void HLightButton::setText(const QString &value)
{
    if (d_ptr->text == value)
        return;
    d_ptr->text = value;
    update();
}

void HLightButton::setTextColor(const QColor &value)
{
    if (d_ptr->textColor == value)
        return;
    d_ptr->textColor = value;
    update();
}

void HLightButton::setAlarmColor(const QColor &value)
{
    if (d_ptr->alarmColor == value)
        return;
    d_ptr->alarmColor = value;
    update();
}

void HLightButton::setNormalColor(const QColor &value)
{
    if (d_ptr->normalColor == value)
        return;
    d_ptr->normalColor = value;
    update();
}

void HLightButton::setBorderOutColorStart(const QColor &value)
{
    if (d_ptr->borderOutColorStart == value)
        return;
    d_ptr->borderOutColorStart = value;
    update();
}

void HLightButton::setBorderOutColorEnd(const QColor &value)
{
    if (d_ptr->borderOutColorEnd == value)
        return;
    d_ptr->borderOutColorEnd = value;
    update();
}

void HLightButton::setBorderInColorStart(const QColor &value)
{
    if (d_ptr->borderInColorStart == value)
        return;
    d_ptr->borderInColorStart = value;
    update();
}

void HLightButton::setBorderInColorEnd(const QColor &value)
{
    if (d_ptr->borderInColorEnd == value)
        return;
    d_ptr->borderInColorEnd = value;
    update();
}

void HLightButton::setBackground(const QColor &value)
{
    if (d_ptr->background == value)
        return;
    d_ptr->background = value;
    update();
}

void HLightButton::setOverlayColor(const QColor &value)
{
    if (d_ptr->overlayColor == value)
        return;
    d_ptr->overlayColor = value;
    update();
}

void HLightButton::setMoveEnable(bool b)
{
    if (d_ptr->moveEnable == b)
        return;
    d_ptr->moveEnable = b;
    d_ptr->filter->setEnable(b);
}

void HLightButton::setShowRect(bool b)
{
    if (d_ptr->showRect == b)
        return;
    d_ptr->showRect = b;
    update();
}

void HLightButton::setShowOverlay(bool b)
{
    if (d_ptr->showOverlay == b)
        return;
    d_ptr->showOverlay = b;
    update();
}

void HLightButton::startAlarm()
{
    if (!d_ptr->timer->isActive())
        d_ptr->timer->start();
}

void HLightButton::stopAlarm()
{
    if (d_ptr->timer->isActive())
        d_ptr->timer->stop();
}

void HLightButton::alarm()
{
    if (d_ptr->isAlarm)
    {
        d_ptr->textColor = QColor(255, 255, 255);
        d_ptr->background = d_ptr->normalColor;
    }
    else
    {
        d_ptr->textColor = QColor(255, 255, 255);
        d_ptr->background  = d_ptr->alarmColor;
    }

    update();
    d_ptr->isAlarm = !d_ptr->isAlarm;
}

void HLightButton::paintEvent(QPaintEvent *)
{
    // 绘制准备工作，启用反锯齿，平移坐标轴中心，等比例缩放
    auto side = qMin(width(), height());
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    if (!isShowRect())
    {
        painter.translate(width() / 2, height() / 2);
        painter.scale(side / 200.0, side / 200.0);
        drawBorderOut(&painter);
        drawBorderIn(&painter);
        drawBackground(&painter);
        drawText(&painter);
        if (isShowOverlay())
            HDrawHelper::drawOverlay(&painter, 80, overlayColor());
    }
    else
        drawRect(&painter);
}

void HLightButton::drawRect(QPainter *painter)
{
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(background());
    painter->drawRoundedRect(this->rect(), 5, 5);
    if (!text().isEmpty())
    {
        auto side = qMin(width(), height());
        auto f = font();
        f.setPixelSize(side - 20);
        painter->setFont(f);
        painter->setPen(textColor());
        painter->drawText(this->rect(), Qt::AlignCenter, text());
    }
    painter->restore();
}

void HLightButton::drawBorderOut(QPainter *painter)
{
    int radius = 99;
    auto gradient = QLinearGradient(0, -radius, 0, radius);
    gradient.setColorAt(0, borderOutColorStart());
    gradient.setColorAt(1, borderOutColorEnd());
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(gradient);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    painter->restore();
}

void HLightButton::drawBorderIn(QPainter *painter)
{
    int radius = 90;
    auto gradient = QLinearGradient(0, -radius, 0, radius);
    gradient.setColorAt(0, borderInColorStart());
    gradient.setColorAt(1, borderInColorEnd());
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(gradient);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    painter->restore();
}

void HLightButton::drawBackground(QPainter *painter)
{
    int radius = 80;
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(background());
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    painter->restore();
}

void HLightButton::drawText(QPainter *painter)
{
    if (text().isEmpty())
        return;

    int radius = 100;
    auto f = font();
    f.setPixelSize(85);
    painter->save();
    painter->setFont(f);
    painter->setPen(textColor());
    painter->drawText(QRect(-radius, -radius, radius * 2, radius * 2), Qt::AlignCenter, text());
    painter->restore();
}

void HLightButton::init()
{
    d_ptr->filter = new HMoveEventFilter(this);
    d_ptr->filter->addWatched(this);
    d_ptr->timer = new QTimer(this);
    d_ptr->timer->setInterval(500);
    connect(d_ptr->timer, &QTimer::timeout, this, &HLightButton::alarm);
}

HE_CONTROL_END_NAMESPACE
