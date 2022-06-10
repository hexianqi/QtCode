#include "HDeviceButton_p.h"
#include "HMoveEventFilter.h"
#include <QtCore/QTimer>
#include <QtGui/QPainter>
#include <QtGui/QMouseEvent>

HE_BEGIN_NAMESPACE

HDeviceButton::HDeviceButton(QWidget *parent) :
    QWidget(parent),
    d_ptr(new HDeviceButtonPrivate)
{
    init();
}

HDeviceButton::HDeviceButton(HDeviceButtonPrivate &p, QWidget *parent) :
    QWidget(parent),
    d_ptr(&p)
{
    init();
}

HDeviceButton::~HDeviceButton()
{
    if (d_ptr->timer->isActive())
        d_ptr->timer->stop();
}

QSize HDeviceButton::sizeHint() const
{
    return {50, 50};
}

QSize HDeviceButton::minimumSizeHint() const
{
    return {10, 10};
}

bool HDeviceButton::isMoveEnable() const
{
    return d_ptr->moveEnable;
}

QString HDeviceButton::text() const
{
    return d_ptr->text;
}

HDeviceButton::ButtonStyle HDeviceButton::buttonStyle() const
{
    return d_ptr->buttonStyle;
}

HDeviceButton::ButtonColor HDeviceButton::buttonColor() const
{
    return d_ptr->buttonColor;
}

void HDeviceButton::setMoveEnable(bool b)
{
    if (d_ptr->moveEnable == b)
        return;
    d_ptr->moveEnable = b;
    d_ptr->filter->setEnable(b);
}

void HDeviceButton::setText(const QString &value)
{
    if (d_ptr->text == value)
        return;
    d_ptr->text = value;
    update();
}

void HDeviceButton::setButtonStyle(ButtonStyle value)
{
    if (d_ptr->buttonStyle == value)
        return;
    d_ptr->buttonStyle = value;
    updatePixmap();
}

void HDeviceButton::setButtonColor(ButtonColor value)
{
    if (d_ptr->buttonColor == value)
        return;
    d_ptr->buttonColor = value;
    updatePixmap();
}

void HDeviceButton::checkAlarm()
{
    if (d_ptr->isDark)
        d_ptr->imageName = QString(":/Resources/fyqy/devicebutton/devicebutton_black_%1.png").arg(d_ptr->type);
    else
        d_ptr->imageName = QString(":/Resources/fyqy/devicebutton/devicebutton_red_%1.png").arg(d_ptr->type);

    d_ptr->isDark = !d_ptr->isDark;
    update();
}

void HDeviceButton::mousePressEvent(QMouseEvent *event)
{
    emit clicked();
    QWidget::mousePressEvent(event);
}

void HDeviceButton::mouseDoubleClickEvent(QMouseEvent *event)
{
    emit doubleClicked();
    QWidget::mouseDoubleClickEvent(event);
}

void HDeviceButton::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    drawPixmap(&painter);
    drawText(&painter);
}

void HDeviceButton::drawPixmap(QPainter *painter)
{
    QPixmap pm(d_ptr->imageName);
    if (!pm.isNull())
        painter->drawPixmap(0, 0, pm.scaled(size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
}

void HDeviceButton::drawText(QPainter *painter)
{
    auto w = width();
    auto h = height();
    auto f = font();
    f.setPointSizeF(h * 0.37);
    f.setBold(true);

    double y = 1.0;
    QRectF rect = this->rect();
    if (d_ptr->buttonStyle == ButtonStyle_Police)
    {
        y = 30 * h / 60.0;
        rect = QRectF(0, y, w, h - y);
    }
    else if (d_ptr->buttonStyle == ButtonStyle_Bubble)
    {
        y = 8 * h / 60.0;
        rect = QRectF(0, 0, w, h - y);
    }
    else if (d_ptr->buttonStyle == ButtonStyle_Bubble2)
    {
        y = 13 * h / 60.0;
        rect = QRectF(0, 0, w, h - y);
        f.setPointSizeF(w * 0.33);
    }
    else if (d_ptr->buttonStyle == ButtonStyle_Msg)
    {
        y = 17 * h / 60.0;
        rect = QRectF(0, 0, w, h - y);
    }
    else if (d_ptr->buttonStyle == ButtonStyle_Msg2)
    {
        y = 17 * h / 60.0;
        rect = QRectF(0, 0, w, h - y);
    }
    painter->setFont(f);
    painter->setPen(Qt::white);
    painter->drawText(rect, Qt::AlignCenter, d_ptr->text);
}

void HDeviceButton::init()
{
    d_ptr->type = "police";
    d_ptr->imageName = QString(":/Resources/fyqy/devicebutton/devicebutton_green_%1.png").arg(d_ptr->type);
    d_ptr->filter = new HMoveEventFilter(this);
    d_ptr->filter->addWatched(this);
    d_ptr->timer = new QTimer(this);
    d_ptr->timer->setInterval(500);
    connect(d_ptr->timer, &QTimer::timeout, this, &HDeviceButton::checkAlarm);
}

void HDeviceButton::updatePixmap()
{
    d_ptr->isDark = false;
    if (d_ptr->timer->isActive())
        d_ptr->timer->stop();

    if (d_ptr->buttonStyle == ButtonStyle_Circle)
        d_ptr->type = "circle";
    else if (d_ptr->buttonStyle == ButtonStyle_Police)
        d_ptr->type = "police";
    else if (d_ptr->buttonStyle == ButtonStyle_Bubble)
        d_ptr->type = "bubble";
    else if (d_ptr->buttonStyle == ButtonStyle_Bubble2)
        d_ptr->type = "bubble2";
    else if (d_ptr->buttonStyle == ButtonStyle_Msg)
        d_ptr->type = "msg";
    else if (d_ptr->buttonStyle == ButtonStyle_Msg2)
        d_ptr->type = "msg2";
    else
        d_ptr->type = "circle";

    if (d_ptr->buttonColor == ButtonColor_Green)
        d_ptr->imageName = QString(":/Resources/fyqy/devicebutton/devicebutton_green_%1.png").arg(d_ptr->type);
    else if (d_ptr->buttonColor == ButtonColor_Blue)
        d_ptr->imageName = QString(":/Resources/fyqy/devicebutton/devicebutton_blue_%1.png").arg(d_ptr->type);
    else if (d_ptr->buttonColor == ButtonColor_Gray)
        d_ptr->imageName = QString(":/Resources/fyqy/devicebutton/devicebutton_gray_%1.png").arg(d_ptr->type);
    else if (d_ptr->buttonColor == ButtonColor_Black)
        d_ptr->imageName = QString(":/Resources/fyqy/devicebutton/devicebutton_black_%1.png").arg(d_ptr->type);
    else if (d_ptr->buttonColor == ButtonColor_Purple)
        d_ptr->imageName = QString(":/Resources/fyqy/devicebutton/devicebutton_purple_%1.png").arg(d_ptr->type);
    else if (d_ptr->buttonColor == ButtonColor_Yellow)
        d_ptr->imageName = QString(":/Resources/fyqy/devicebutton/devicebutton_yellow_%1.png").arg(d_ptr->type);
    else if (d_ptr->buttonColor == ButtonColor_Red)
    {
        checkAlarm();
        if (!d_ptr->timer->isActive())
            d_ptr->timer->start();
    }
    update();
}

HE_END_NAMESPACE
