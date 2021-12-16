#include "HDefenceButton_p.h"
#include "HMoveEventFilter.h"
#include <QtCore/QTimer>
#include <QtGui/QPainter>
#include <QtGui/QPixmapCache>
#include <QtGui/QMouseEvent>

HE_BEGIN_NAMESPACE

HDefenceButton::HDefenceButton(QWidget *parent) :
    QWidget(parent),
    d_ptr(new HDefenceButtonPrivate)
{
    init();
}

HDefenceButton::HDefenceButton(HDefenceButtonPrivate &p, QWidget *parent) :
    QWidget(parent),
    d_ptr(&p)
{
    init();
}

HDefenceButton::~HDefenceButton()
{
    if (d_ptr->timer->isActive())
        d_ptr->timer->stop();
}

QSize HDefenceButton::sizeHint() const
{
    return {50, 50};
}

QSize HDefenceButton::minimumSizeHint() const
{
    return {10, 10};
}

bool HDefenceButton::isMoveEnable() const
{
    return d_ptr->moveEnable;
}

QString HDefenceButton::text() const
{
    return d_ptr->text;
}

HDefenceButton::ButtonStyle HDefenceButton::buttonStyle() const
{
    return d_ptr->buttonStyle;
}

HDefenceButton::ButtonStatus HDefenceButton::buttonStatus() const
{
    return d_ptr->buttonStatus;
}

void HDefenceButton::setMoveEnable(bool b)
{
    if (d_ptr->moveEnable == b)
        return;
    d_ptr->moveEnable = b;
    d_ptr->filter->setEnable(b);
}

void HDefenceButton::setText(const QString &value)
{
    if (d_ptr->text == value)
        return;
    d_ptr->text = value;
    update();
}

void HDefenceButton::setButtonStyle(ButtonStyle value)
{
    if (d_ptr->buttonStyle == value)
        return;
    d_ptr->buttonStyle = value;
    updatePixmap();
}

void HDefenceButton::setButtonStatus(ButtonStatus value)
{
    if (d_ptr->buttonStatus == value)
        return;
    d_ptr->buttonStatus = value;
    updatePixmap();
}

void HDefenceButton::alarm()
{
    if (d_ptr->isDark)
        d_ptr->imageName = QString(":/image/ludianwu/defence_button_error_%1.png").arg(d_ptr->type);
    else
        d_ptr->imageName = QString(":/image/ludianwu/defence_button_alarm_%1.png").arg(d_ptr->type);

    d_ptr->isDark = !d_ptr->isDark;
    update();
}

void HDefenceButton::mousePressEvent(QMouseEvent *event)
{
    emit clicked();
    QWidget::mousePressEvent(event);
}

void HDefenceButton::mouseDoubleClickEvent(QMouseEvent *event)
{
    emit doubleClicked();
    QWidget::mouseDoubleClickEvent(event);
}

void HDefenceButton::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    drawPixmap(&painter);
    drawText(&painter);
}

void HDefenceButton::drawPixmap(QPainter *painter)
{
    QPixmap pm;
    if (!QPixmapCache::find(d_ptr->imageName, &pm))
    {
        pm.load(d_ptr->imageName);
        QPixmapCache::insert(d_ptr->imageName, pm);
    }
    if (!pm.isNull())
        painter->drawPixmap(0, 0, pm.scaled(size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
}

void HDefenceButton::drawText(QPainter *painter)
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

void HDefenceButton::init()
{
    d_ptr->type = "police";
    d_ptr->imageName = QString(":/image/ludianwu/defence_button_disarming_%1.png").arg(d_ptr->type);
    d_ptr->filter = new HMoveEventFilter(this);
    d_ptr->filter->addWatched(this);
    d_ptr->timer = new QTimer(this);
    d_ptr->timer->setInterval(500);
    connect(d_ptr->timer, &QTimer::timeout, this, &HDefenceButton::alarm);
}

void HDefenceButton::updatePixmap()
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

    if (d_ptr->buttonStatus == ButtonStatus_Arming)
        d_ptr->imageName = QString(":/image/ludianwu/defence_button_arming_%1.png").arg(d_ptr->type);
    else if (d_ptr->buttonStatus == ButtonStatus_Disarming)
        d_ptr->imageName = QString(":/image/ludianwu/defence_button_disarming_%1.png").arg(d_ptr->type);
    else if (d_ptr->buttonStatus == ButtonStatus_Bypass)
        d_ptr->imageName = QString(":/image/ludianwu/defence_button_bypass_%1.png").arg(d_ptr->type);
    else if (d_ptr->buttonStatus == ButtonStatus_Error)
        d_ptr->imageName = QString(":/image/ludianwu/defence_button_error_%1.png").arg(d_ptr->type);
    else if (d_ptr->buttonStatus == ButtonStatus_Alarm)
    {
        alarm();
        if (!d_ptr->timer->isActive())
            d_ptr->timer->start();
    }
    update();
}

HE_END_NAMESPACE
