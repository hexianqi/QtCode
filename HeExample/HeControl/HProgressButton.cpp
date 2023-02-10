#include "HProgressButton_p.h"
#include <QtCore/QTimer>
#include <QtCore/QVariantAnimation>
#include <QtGui/QPainter>

HE_BEGIN_NAMESPACE

HProgressButton::HProgressButton(QWidget *parent) :
    QWidget(parent),
    d_ptr(new HProgressButtonPrivate)
{
    auto font = this->font();
    font.setPixelSize(24);
    setFont(font);
    setMouseTracking(true);
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground, true);
    setFixedHeight(60);
    setMinimumWidth(140);

    d_ptr->timer = new QTimer(this);
    d_ptr->timer->setInterval(40);
    connect(d_ptr->timer,&QTimer::timeout,this, &HProgressButton::onTimeout);
    connect(this, &HProgressButton::startProcessing, this, &HProgressButton::operationProcessing, Qt::QueuedConnection);
}

HProgressButton::~HProgressButton()
{
}

void HProgressButton::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);

    if (d_ptr->buttonState == Normal || d_ptr->buttonState == Hover)
    {
        QPainterPath path;
        path.addRoundedRect(rect(), 30, 30);
        painter.setClipPath(path);
        painter.fillRect(rect(), Qt::white);
        painter.save();
        painter.setBrush(QColor(d_ptr->buttonState == Normal ? 0x51c582 : 0x37be77));
        painter.setPen(Qt::transparent);
        painter.drawRoundedRect(rect().adjusted(3, 3, -3, -3), 30, 30);
        painter.restore();
        painter.setPen(Qt::white);
        painter.setFont(this->font());
        painter.drawText(rect(), Qt::AlignCenter, d_ptr->text);
    }
    else if (d_ptr->buttonState == Corner || d_ptr->buttonState == Recovery)
    {
        painter.setBrush(QColor(0x51c582));
        painter.setPen(QPen(QColor(0x45B078),3));
        painter.translate(rect().center());
        painter.drawRoundedRect(-d_ptr->widthChangeValue, -height() / 2 + 3, d_ptr->widthChangeValue * 2, height() - 6, 30, 30);
    }
    else if (d_ptr->buttonState == OpenProgress)
    {
        auto radiu = (height() - 6) / 2 - 3;
        auto angle = d_ptr->progress * 360 / 100;
        painter.translate(rect().center());
        painter.setBrush(QColor(0x51c582));
        painter.setPen(QPen(QColor(0x45B078), 3));
        painter.drawEllipse(QPoint(0, 0), radiu, radiu);
        painter.setPen(QPen(Qt::white, 3));
        painter.drawArc(QRect(-radiu - 3, -radiu - 3, radiu * 2 + 6, radiu * 2 + 6), 90 * 16, -angle * 16);
    }
    else if (d_ptr->buttonState == CloseProgress)
    {
        auto radiu = (height() - 6) / 2;
        painter.translate(rect().center());
        painter.setPen(Qt::transparent);
        painter.setBrush(QColor(0, 0, 0, 63));
        painter.drawEllipse(QPoint(0, 0) ,radiu, radiu);

        radiu -= 3;
        painter.setBrush(Qt::white);
        painter.drawEllipse(QPoint(0,0 ),radiu,radiu);

        painter.setPen(QPen(QColor("#4DAF51"), 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        painter.drawLine(-radiu / 3, 0, -radiu / 5, radiu / 3);
        painter.drawLine(-radiu / 5, radiu / 3, radiu / 4, -radiu / 4);
    }
}

void HProgressButton::enterEvent(QEvent *event)
{
    if (d_ptr->buttonState == Normal)
    {
        d_ptr->buttonState = Hover;
        update();
    }
    QWidget::enterEvent(event);
}

void HProgressButton::leaveEvent(QEvent *event)
{
    if (d_ptr->buttonState == Hover)
    {
        d_ptr->buttonState = Normal;
        update();
    }
    QWidget::leaveEvent(event);
}

void HProgressButton::mousePressEvent(QMouseEvent *event)
{
    if (d_ptr->buttonState == Hover || d_ptr->buttonState == Normal)
    {
        d_ptr->buttonState = Corner;
        d_ptr->widthChangeValue = (width() - 6) / 2;
        d_ptr->timer->start();
        update();
    }
    else if (d_ptr->buttonState == CloseProgress)
    {
        d_ptr->buttonState = Recovery;
        d_ptr->timer->start();
        update();
    }
    QWidget::mousePressEvent(event);
}

void HProgressButton::onTimeout()
{
    if (d_ptr->buttonState == Corner)
    {
        d_ptr->widthChangeValue -= width() * 0.05;
        if (d_ptr->widthChangeValue <= height())
        {
            d_ptr->buttonState = OpenProgress;
            d_ptr->progress = 0;
            d_ptr->timer->stop();
            emit startProcessing();
        }
    }
    else
    {
        d_ptr->widthChangeValue += this->width() * 0.05;
        if (d_ptr->widthChangeValue >= width() / 2)
        {
            d_ptr->buttonState = Normal;
            d_ptr->timer->stop();
        }
    }
    update();
}

void HProgressButton::operationProcessing()
{
    for (int i = 0; i < 500000000; i++)
    {
        if (i % 5000000 == 0)
        {
            d_ptr->progress++;
            repaint();
        }
    }

    if (d_ptr->progress == 100)
    {
        d_ptr->buttonState = CloseProgress;
        update();
        auto waterDrop = new HWaterDrop();
        waterDrop->move(mapToGlobal(rect().center()));
        waterDrop->show();
    }
}

const int RADIUS = 60;

HWaterDrop::HWaterDrop(QWidget *parent)
    : QWidget(parent)
{
    setFixedSize(QSize(RADIUS * 2, RADIUS * 2));
    setWindowFlags(Qt::FramelessWindowHint | Qt::Tool);
    setAttribute(Qt::WA_TranslucentBackground);
    setAttribute(Qt::WA_DeleteOnClose);
    _waterDropAnimation = new QVariantAnimation(this);
    connect(_waterDropAnimation, &QVariantAnimation::valueChanged, this, &HWaterDrop::onRaduisChanged);
    connect(_waterDropAnimation, &QVariantAnimation::finished, this, &HWaterDrop::close);
}

//把鼠标点击的点转换为圆心点坐标
void HWaterDrop::move(const QPoint &point)
{
    QWidget::move(point - QPoint(RADIUS, RADIUS));
}

void HWaterDrop::show()
{
    _waterDropAnimation->setStartValue(0);
    _waterDropAnimation->setEndValue(RADIUS);
    _waterDropAnimation->setDuration(350);
    _waterDropAnimation->start();
    QWidget::show();
}

void HWaterDrop::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(QPen(QColor(0xffffff80), 5));
    painter.drawEllipse(rect().center(), _animationRadius, _animationRadius);
}

void HWaterDrop::onRaduisChanged(QVariant value)
{
    _animationRadius = value.toInt();
    update();
}

HE_END_NAMESPACE

