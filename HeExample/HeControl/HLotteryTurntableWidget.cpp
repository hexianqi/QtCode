#include "HLotteryTurntableWidget_p.h"
#include <QtGui/QtEvents>
#include <QtGui/QPainter>
#include <QtCore/QPropertyAnimation>
#include <QtCore/QRandomGenerator>

HE_BEGIN_NAMESPACE

HLotteryTurntableWidget::HLotteryTurntableWidget(QWidget *parent) :
    QWidget(parent),
    d_ptr(new HLotteryTurntableWidgetPrivate)
{
    init();
}

HLotteryTurntableWidget::HLotteryTurntableWidget(HLotteryTurntableWidgetPrivate &p, QWidget *parent) :
    QWidget(parent),
    d_ptr(&p)
{
    init();
}

HLotteryTurntableWidget::~HLotteryTurntableWidget()
{
}

int HLotteryTurntableWidget::rotate()
{
    return d_ptr->rotate;
}

void HLotteryTurntableWidget::setRotate(int value)
{
    if (d_ptr->rotate == value)
        return;

    d_ptr->rotate = value;
    update();
}

void HLotteryTurntableWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);  //反走样开启

    int i;
    int smallEllipse;
    auto radius = std::min(width(), height()) / 2 - 25;

    painter.save();
    painter.translate(rect().center());
    painter.setPen(QPen(QColor("#F0630B"), 16));
    painter.drawEllipse(QPoint(0, 0), radius, radius);

    radius -= 8;
    painter.setPen(QPen(QColor("#FF4500"), 8));
    painter.drawEllipse(QPoint(0, 0), radius, radius);

    radius -= 24;
    painter.setPen(QPen(QColor("#B71606"), 48));
    painter.drawEllipse(QPoint(0, 0), radius, radius);

    painter.save();
    if (!d_ptr->isRuning)
    {
        painter.setPen(Qt::white);
        painter.setBrush(Qt::white);
    }
    for (i = 0; i < 20; i++)
    {
        painter.rotate(18.0);
        if (i % 2 == 0)
        {
            if (d_ptr->isRuning)
            {
                if (d_ptr->rotate % 2 == 0)
                {
                    painter.setPen(Qt::red);
                    painter.setBrush(Qt::red);
                }
                else
                {
                    painter.setPen(Qt::blue);
                    painter.setBrush(Qt::blue);
                }
            }
            smallEllipse = 15;
        }
        else
        {
            if (d_ptr->isRuning)
            {
                if (d_ptr->rotate % 2 == 0)
                {
                    painter.setPen(Qt::blue);
                    painter.setBrush(Qt::blue);
                }
                else
                {
                    painter.setPen(Qt::red);
                    painter.setBrush(Qt::red);
                }
            }
            smallEllipse = 10;
        }
        painter.drawEllipse(QPoint(radius, 0), smallEllipse, smallEllipse);
    }
    painter.restore();

    radius -= 30;
    painter.setPen(QPen(QColor("#FFC228"), 20));
    painter.drawEllipse(QPoint(0, 0), radius, radius);

    radius -= 30;
    painter.setPen(QPen(QColor("#FFC228"), 20));
    painter.drawEllipse(QPoint(0, 0), radius, radius);

    radius -= 10;
    auto centerRect = QRect(-radius, -radius, radius * 2, radius * 2);

    painter.setPen(Qt::transparent);
    painter.save();
    painter.rotate(18.0 * d_ptr->rotate);
    for (i = 0; i < 8; i++)
    {
        QPainterPath path;
        path.moveTo(0,0);
        path.arcTo(centerRect, 45 * i,45);
        path.closeSubpath();
        painter.fillPath(path, d_ptr->colors[i]);
    }
    painter.restore();

    QPainterPath trianglePath;//三角形
    QPolygon polygon;
    polygon.append(QPoint(0, -radius * 0.55));
    polygon.append(QPoint(-radius * 0.25, 0));
    polygon.append(QPoint(radius * 0.25, 0));
    trianglePath.addPolygon(polygon);
    painter.setBrush(QColor("#EEDAA2"));
    painter.drawPath(trianglePath);

    painter.setBrush(QColor("#FDFAEA"));
    radius = static_cast<int>(radius * 0.3);
    painter.drawEllipse(QPoint(0, 0), radius, radius);

    radius -= 2;
    painter.setBrush(d_ptr->isPressCenter ? QColor("#B91A0D").lighter() : QColor("#B91A0D"));//中间的按钮
    painter.drawEllipse(QPoint(0, 0), radius, radius);
    painter.restore();

    d_ptr->centerRect = QRegion(width() / 2 - radius, height() / 2 - radius, radius * 2, radius * 2, QRegion::Ellipse);
}

void HLotteryTurntableWidget::mousePressEvent(QMouseEvent *event)
{
    if (!d_ptr->isRuning)
    {
        d_ptr->isPressCenter = d_ptr->centerRect.contains(event->pos());
        if (d_ptr->isPressCenter)
        {
            d_ptr->isRuning = true;

            auto animation = new QPropertyAnimation(this, "rotate");
            animation->setEasingCurve(QEasingCurve::InOutCubic);
            animation->setDuration(3000);
            animation->setStartValue(0);
            animation->setEndValue(QRandomGenerator::global()->bounded(360) + 360 * 5);
            connect(animation, &QAbstractAnimation::finished, this, [=] { d_ptr->isRuning = false; });
            animation->start(QAbstractAnimation::DeleteWhenStopped);
            update();
        }

    }
    QWidget::mousePressEvent(event);
}

void HLotteryTurntableWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (d_ptr->isPressCenter)
    {
        d_ptr->isPressCenter = false;
        update();
    }
    QWidget::mouseReleaseEvent(event);
}

void HLotteryTurntableWidget::init()
{
    setPalette(Qt::white);
    setMinimumSize(500, 500);
    d_ptr->colors << Qt::red << Qt::yellow << Qt::green << Qt::cyan << Qt::blue << Qt::magenta << Qt::darkGreen << Qt::darkCyan;
}

HE_END_NAMESPACE

