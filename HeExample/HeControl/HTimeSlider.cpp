#include "HTimeSlider_p.h"
#include <QtGui/QPainter>
#include <QtGui/QtEvents>

HE_BEGIN_NAMESPACE

HTimeSlider::HTimeSlider(QWidget *parent) :
    QWidget(parent),
    d_ptr(new HTimeSliderPrivate)
{
    init();
}

HTimeSlider::HTimeSlider(HTimeSliderPrivate &p, QWidget *parent) :
    QWidget(parent),
    d_ptr(&p)
{
    init();
}

HTimeSlider::~HTimeSlider()
{
}

void HTimeSlider::setSec(int value)
{
    if (d_ptr->sec == value)
        return;
    d_ptr->sec = value;
    update();
}

void HTimeSlider::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.save();
    painter.setRenderHint(QPainter::Antialiasing,true);

    auto frayLineRect = QRect(0, (height() - 6) / 2, width(), 6);

    painter.setPen(Qt::transparent);
    painter.setBrush(QColor("#c6c6c6"));
    painter.drawRoundedRect(frayLineRect, 3, 3);

    auto font = this->font();
    font.setPointSize(16);
    painter.setFont(font);
    auto text = QString("%1/%2").arg(digitalToTime(d_ptr->currentSec), digitalToTime(d_ptr->sec));

    d_ptr->textRect = painter.boundingRect(QRect(0, frayLineRect.center().y(), 0, 0), Qt::AlignLeft | Qt::AlignVCenter, text);

    auto efficientAllWidth = width() - d_ptr->textRect.width();
    auto efficientWidth = efficientAllWidth * d_ptr->currentSec / d_ptr->sec;

    d_ptr->textRect.moveLeft(efficientWidth);

    frayLineRect.setWidth(efficientWidth);
    painter.setPen(Qt::transparent);
    painter.setBrush(QColor("#800080"));
    painter.drawRoundedRect(frayLineRect, 3, 3);

    painter.setBrush(QColor("#020202"));
    painter.drawRoundedRect(d_ptr->textRect, 6, 6);
    painter.setPen(QPen(Qt::white, 5));
    painter.drawText(d_ptr->textRect, text);
    painter.restore();
}

void HTimeSlider::mousePressEvent(QMouseEvent *event)
{
    if (d_ptr->textRect.contains(event->pos()))
    {
        d_ptr->isPress = true;
    }
    else
    {
        d_ptr->currentSec = qBound(0, event->x() * d_ptr->sec / (width() - d_ptr->textRect.width()), d_ptr->sec);
        update();
    }
    QWidget::mousePressEvent(event);
}

void HTimeSlider::mouseReleaseEvent(QMouseEvent *event)
{
    d_ptr->isPress = false;
    QWidget::mouseReleaseEvent(event);
}

void HTimeSlider::mouseMoveEvent(QMouseEvent *event)
{
    if (d_ptr->isPress)
    {
        d_ptr->currentSec = qBound(0, event->x() * d_ptr->sec / (width() - d_ptr->textRect.width()), d_ptr->sec);
        update();
    }
    QWidget::mouseMoveEvent(event);
}

void HTimeSlider::init()
{
    setPalette(Qt::white);
    setMinimumSize(250, 60);
}

QString HTimeSlider::digitalToTime(int sec)
{
    auto h = sec / 3600;
    auto m = sec % 3600 / 60;
    auto s = sec % 60;
    return QString("%1:%2").arg(h * 60 + m).arg(s);
}

HE_END_NAMESPACE

