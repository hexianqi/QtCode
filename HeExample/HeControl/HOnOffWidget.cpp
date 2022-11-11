#include "HOnOffWidget_p.h"
#include <QtCore/QTimer>
#include <QtGui/QPainter>
#include <QtGui/QMouseEvent>

HE_BEGIN_NAMESPACE

HOnOffWidget::HOnOffWidget(QWidget *parent) :
    QWidget(parent),
    d_ptr(new HOnOffWidgetPrivate)
{
    d_ptr->timer = new QTimer(this);
    d_ptr->timer->setInterval(40);
    connect(d_ptr->timer, &QTimer::timeout, this, &HOnOffWidget::onTimer);

    QTimer::singleShot(100, [&]
                       {
                           d_ptr->x = rect().adjusted(3, 3, -3, -3).x() + 2.0;
                           update();
                       });
}


HOnOffWidget::~HOnOffWidget()
{
}

void HOnOffWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.save();
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform | QPainter::TextAntialiasing);
    painter.setPen(Qt::transparent);

    QRect innerRect;
    auto outRoundRect = rect().adjusted(3, 3, -3, -3);

    if (d_ptr->x > outRoundRect.x() + outRoundRect.width() * 0.45 - 2 || d_ptr->x < outRoundRect.x() + 2.0)
    {
        d_ptr->x = qBound(outRoundRect.x() + 2.0, d_ptr->x, outRoundRect.x() + outRoundRect.width() * 0.45 - 2);
        if (d_ptr->runing)
        {
            d_ptr->timer->stop();
            d_ptr->runing = false;
        }
    }

    if (d_ptr->isOn)
    {
        if (d_ptr->runing)
        {
            painter.setBrush(QColor("#E7E7E7"));
            innerRect = QRect(d_ptr->x, outRoundRect.y() + 2, outRoundRect.width() * 0.55, outRoundRect.height() - 4);
        }
        else
        {
            painter.setBrush(QColor("#D93152"));
            innerRect = QRect(outRoundRect.x() + outRoundRect.width() * 0.45 - 2 , outRoundRect.y() + 2, outRoundRect.width() * 0.55, outRoundRect.height() - 4);
        }
    }
    else
    {
        if (d_ptr->runing)
        {
            innerRect = QRect(d_ptr->x, outRoundRect.y() + 2, outRoundRect.width() * 0.55, outRoundRect.height() - 4);
            painter.setBrush(QColor("#D93152"));
        }
        else
        {
            painter.setBrush(QColor("#E7E7E7"));
            innerRect = QRect(outRoundRect.x() + 2, outRoundRect.y() + 2, outRoundRect.width() * 0.55, outRoundRect.height() - 4);
        }
    }
    painter.drawRoundRect(outRoundRect, 6, 6);
    painter.setBrush(Qt::white);
    painter.drawRoundRect(innerRect, 8, 8);
    painter.restore();
}

void HOnOffWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        d_ptr->isOn = !d_ptr->isOn;
        d_ptr->timer->start();
    }
    return QWidget::mousePressEvent(event);
}

void HOnOffWidget::onTimer()
{
    d_ptr->runing = true;
    if (d_ptr->isOn)
        d_ptr->x += rect().width() * 0.072;
    else
        d_ptr->x -= rect().width() * 0.072;
    update();
}

HE_END_NAMESPACE


