#include "HRotatingClockWidget_p.h"
#include <QtCore/QTime>
#include <QtCore/QTimer>
#include <QtGui/QPainter>

HE_BEGIN_NAMESPACE

HRotatingClockWidget::HRotatingClockWidget(QWidget *parent) :
    QWidget(parent),
    d_ptr(new HRotatingClockWidgetPrivate)
{
    d_ptr->secondTimer = new QTimer(this);
    d_ptr->animationTimer = new QTimer(this);
    connect(d_ptr->secondTimer, &QTimer::timeout, this, &HRotatingClockWidget::onSecondTimer);
    connect(d_ptr->animationTimer, &QTimer::timeout, this, &HRotatingClockWidget::onAnimationTimer);
    d_ptr->secondTimer->start(1000);
    d_ptr->animationTimer->setInterval(40);
}

HRotatingClockWidget::~HRotatingClockWidget()
{
}

void HRotatingClockWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    int i, temp;
    auto distance = (std::min(width(), height()) - 20) / 13.6;
    auto center = QPointF(rect().center());

    painter.save();
    painter.setRenderHint(QPainter::Antialiasing,true);
    painter.setPen(QPen(Qt::white, 4, Qt::SolidLine, Qt::RoundCap));
    painter.drawLine(center.x(), center.y() - distance * 0.2, center.x() + distance * 0.2, center.y());
    painter.drawLine(center.x() + distance * 0.2, center.y(), center.x(), center.y() + distance * 0.2);

    QColor color(218, 165, 32);
    painter.setPen(QPen(color, 5));
    painter.drawEllipse(center, distance * 0.8, distance * 0.8);
    painter.drawEllipse(center, distance * 2.8, distance * 2.8);
    painter.drawEllipse(center, distance * 4.8, distance * 4.8);
    painter.drawEllipse(center, distance * 6.8, distance * 6.8);

    color.setAlpha(100);
    painter.setPen(QPen(color, 3));
    painter.drawEllipse(center, distance * 1.8, distance * 1.8);
    painter.drawEllipse(center, distance * 3.8, distance * 3.8);
    painter.drawEllipse(center, distance * 5.8, distance * 5.8);

    color.setAlpha(255);
    painter.setPen(QPen(color));
    auto font = this->font();
    font.setPixelSize(distance * 0.66);
    font.setBold(true);
    painter.setFont(font);
    painter.translate(center);

    temp = processPlace(d_ptr->hourTenPlace - 1, 2);
    for (i = 0; i <= 2; i++)
    {
        painter.save();
        if (Q_UNLIKELY(d_ptr->hourTenPlaceRotate > 0))
            painter.rotate(120 * (i - temp) - d_ptr->hourTenPlaceRotate);
        else
            painter.rotate(120 * (i - d_ptr->hourTenPlace));
        if (d_ptr->hourTenPlace == i)
            painter.setPen(Qt::red);
        painter.drawText(distance * 0.8, -distance * 0.8, distance, distance * 1.6, Qt::AlignCenter, QString::number(i));
        painter.restore();
    }

    temp = processPlace(d_ptr->hourOnePlace - 1, 9);
    for (i = 0; i <= 9; i++)
    {
        painter.save();
        if (Q_UNLIKELY(d_ptr->hourOnePlaceRotate > 0))
            painter.rotate(36 * (i - temp) - d_ptr->hourOnePlaceRotate);
        else
            painter.rotate(36 * (i - d_ptr->hourOnePlace));
        if (d_ptr->hourOnePlace == i)
            painter.setPen(Qt::red);
        painter.drawText(distance * 1.8, -distance * 0.8, distance, distance * 1.6, Qt::AlignCenter, QString::number(i));
        painter.restore();
    }

    temp = processPlace(d_ptr->minuteTenPlace - 1, 5);
    for (i = 0; i <= 5; i++)
    {
        painter.save();
        if (Q_UNLIKELY(d_ptr->minuteTenPlaceRotate > 0))
            painter.rotate(60 * (i - temp) - d_ptr->minuteTenPlaceRotate);
        else
            painter.rotate(60 * (i - d_ptr->minuteTenPlace));
        if (d_ptr->minuteTenPlace == i)
            painter.setPen(Qt::red);
        painter.drawText(distance * 2.8, -distance * 0.8, distance, distance * 1.6, Qt::AlignCenter, QString::number(i));
        painter.restore();
    }

    temp = processPlace(d_ptr->minuteOnePlace - 1, 9);
    for (i = 0; i <= 9; i++)
    {
        painter.save();
        if (Q_UNLIKELY(d_ptr->minuteOnePlaceRotate > 0))
            painter.rotate(36 * (i - temp) - d_ptr->minuteOnePlaceRotate);
        else
            painter.rotate(36 * (i - d_ptr->minuteOnePlace));
        if (d_ptr->minuteOnePlace == i)
            painter.setPen(Qt::red);
        painter.drawText(distance * 3.8, -distance * 0.8, distance, distance * 1.6, Qt::AlignCenter, QString::number(i));
        painter.restore();
    }

    temp = processPlace(d_ptr->secondTenPlace - 1, 9);
    for (i = 0; i <= 5; i++)
    {
        painter.save();
        if (d_ptr->secondTenPlaceRotate > 0)
            painter.rotate(60 * (i - temp) - d_ptr->secondTenPlaceRotate);
        else
            painter.rotate(60 * (i - d_ptr->secondTenPlace));

        if (d_ptr->secondTenPlace == i)
            painter.setPen(Qt::red);
        painter.drawText(distance * 4.8, -distance * 0.8, distance, distance * 1.6, Qt::AlignCenter,QString::number(i));
        painter.restore();
    }

    temp = processPlace(d_ptr->secondOnePlace - 1, 9);
    for (int i = 0;i <= 9;++i)
    {
        painter.save();
        if (d_ptr->secondOnePlaceRotate > 0)
            painter.rotate(36 * (i - temp) - d_ptr->secondOnePlaceRotate);
        else
            painter.rotate(36 * (i - d_ptr->secondOnePlace));

        if (d_ptr->secondOnePlace == i)
            painter.setPen(Qt::red);
        painter.drawText(distance * 5.8, -distance * 0.8, distance, distance * 1.6, Qt::AlignCenter, QString::number(i));
        painter.restore();
    }
    painter.restore();
}

void HRotatingClockWidget::onSecondTimer()
{
    auto time = QTime::currentTime();
    auto second = time.second();
    auto minute = time.minute();
    auto hour = time.hour();

    d_ptr->secondOnePlace = second % 10;
    if (d_ptr->secondTenPlace != second / 10 % 10)
    {
        d_ptr->secondTenPlace = second / 10 % 10;
        d_ptr->secondTenPlaceRotate = 0;
    }
    if (d_ptr->minuteOnePlace != minute % 10)
    {
        d_ptr->minuteOnePlace = minute % 10;
        d_ptr->minuteOnePlaceRotate = 0;
    }
    if (d_ptr->minuteTenPlace != minute / 10 % 10)
    {
        d_ptr->minuteTenPlace = minute / 10 % 10;
        d_ptr->minuteTenPlaceRotate = 0;
    }
    if (d_ptr->hourOnePlace != hour % 10)
    {
        d_ptr->hourOnePlace = hour % 10;
        d_ptr->hourOnePlaceRotate = 0;
    }
    if (d_ptr->hourTenPlace != hour / 10 % 10)
    {
        d_ptr->hourTenPlace = hour / 10 % 10;
        d_ptr->hourTenPlaceRotate = 0;
    }

    d_ptr->animationTimer->start();
}

void HRotatingClockWidget::onAnimationTimer()
{
    d_ptr->secondOnePlaceRotate += 3;
    if (d_ptr->secondOnePlaceRotate >= 36)
    {
        d_ptr->secondOnePlaceRotate = 0;
        d_ptr->animationTimer->stop();
    }

    processRotate(d_ptr->secondTenPlaceRotate, 60);
    processRotate(d_ptr->minuteOnePlaceRotate, 36);
    processRotate(d_ptr->minuteTenPlaceRotate, 60);
    processRotate(d_ptr->hourOnePlaceRotate, 36);
    processRotate(d_ptr->hourTenPlaceRotate, 120);
    update();
}

int HRotatingClockWidget::processRotate(int value, int max)
{
    if (value < 0)
        return value;
    if (value >= max)
        return -1;
    return value + max / 12;
}

int HRotatingClockWidget::processPlace(int value, int max)
{
    if (value > max)
        return 0;
    if (value < 0)
        return max;
    return value;
}

HE_END_NAMESPACE
