#include "HPatternLockWidget_p.h"
#include <QtCore/QTimer>
#include <QtGui/QtEvents>
#include <QtGui/QPainter>

HE_BEGIN_NAMESPACE

HPatternLockWidget::HPatternLockWidget(int number, QWidget *parent) :
    QWidget(parent),
    d_ptr(new HPatternLockWidgetPrivate)
{
    d_ptr->hoverTimer = new QTimer(this);
    d_ptr->hoverTimer->setInterval(40);
    connect(d_ptr->hoverTimer, &QTimer::timeout, this ,&HPatternLockWidget::onHoverTimer);
    setNumber(number);
    setMouseTracking(true);
    setMinimumSize(400,400);
}

HPatternLockWidget::~HPatternLockWidget()
{
}

int HPatternLockWidget::number() const
{
    return d_ptr->number;
}

QString HPatternLockWidget::password()
{
    QString psw;
    for (auto value : d_ptr->sets)
        psw.append(QString("%1").arg(value, 2, 16, QChar('0')));
    return psw;
}

void HPatternLockWidget::setNumber(int value)
{
    if (value < 1 || value > 9 || d_ptr->number == value)
        return;

    reset();
    d_ptr->circularStates.clear();
    d_ptr->circularRects.clear();
    d_ptr->number = value;
    for (int i = 0; i < d_ptr->number; i++)
    {
        for (int j = 0;j < d_ptr->number;j++)
        {
            d_ptr->circularStates << Normal;
            d_ptr->circularRects << QRect();
        }
    }
    update();
}

void HPatternLockWidget::reset()
{
    d_ptr->patterneLockState = NotSet;
    d_ptr->circularStates.fill(Normal);
    d_ptr->lastHoverIndex = -1;
    d_ptr->hoverTimer->stop();
    d_ptr->currentOffset = 0;
    d_ptr->isUpdateCircular = true;
    d_ptr->mouseInCircular = false;
    d_ptr->settingMousPos = QPoint(0,0);
    d_ptr->sets.clear();
    update();
}

void HPatternLockWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    auto mustUpdateCircular = d_ptr->isUpdateCircular;
    auto sideLength = std::min(width(), height()) - 20.0;
    auto drawZoneRect = QRectF(-sideLength / 2.0, -sideLength / 2.0, sideLength, sideLength);
    drawZoneRect.translate(rect().center());

    painter.setRenderHint(QPainter::Antialiasing,true);
    painter.save();
    painter.fillRect(rect(), QColor("#1D1D1D"));
    painter.setPen(QPen(QColor("#141414"), 5));
    painter.drawRoundedRect(drawZoneRect, 12, 12);
    painter.restore();

    d_ptr->radiu = sideLength / (d_ptr->number * 5 - 1);
    for (int i = 0, index = 0; i < d_ptr->number; i++)
    {
        for (int j = 0; j < d_ptr->number; j++, index++)
        {
            auto color = QColor(Qt::white);
            auto center = drawZoneRect.topLeft() + QPointF(d_ptr->radiu * (2 + j * 5), d_ptr->radiu * (2 + i * 5));
            if (mustUpdateCircular)
            {
                auto newCircularRect = QRect(-d_ptr->radiu / 2, -d_ptr->radiu / 2, d_ptr->radiu, d_ptr->radiu);
                newCircularRect.translate(center.toPoint());
                d_ptr->circularRects[index] = newCircularRect;
            }
            if (d_ptr->sets.contains(index))
                color = d_ptr->patterneLockState == Setting || d_ptr->patterneLockState == Valid ? QColor("#00FF80") : QColor("#FE4C40");
            painter.setPen(QPen(color, 3));
            if (index == d_ptr->lastHoverIndex && d_ptr->hoverTimer->isActive() && d_ptr->patterneLockState == Setting)
                painter.drawEllipse(center, d_ptr->radiu + d_ptr->currentOffset, d_ptr->radiu + d_ptr->currentOffset);
            else
                painter.drawEllipse(center, d_ptr->radiu, d_ptr->radiu);

            painter.save();
            painter.setPen(Qt::transparent);
            if (d_ptr->circularStates.at(index) == Normal)
            {
                if (index == d_ptr->lastHoverIndex && d_ptr->hoverTimer->isActive() && d_ptr->patterneLockState == NotSet)
                {
                    painter.setBrush(Qt::white);
                    painter.drawEllipse(center, d_ptr->radiu * 0.5 + d_ptr->currentOffset, d_ptr->radiu * 0.5 + d_ptr->currentOffset);
                }
                else
                {
                    painter.setBrush(QColor("#888888"));
                    painter.drawEllipse(center, d_ptr->radiu * 0.5, d_ptr->radiu * 0.5);
                }
            }
            else
            {
                if (d_ptr->patterneLockState == NotSet)
                {
                    painter.setBrush(Qt::white);
                    if (d_ptr->hoverTimer->isActive())
                        painter.drawEllipse(center, d_ptr->radiu * 0.5 + d_ptr->currentOffset, d_ptr->radiu * 0.5 + d_ptr->currentOffset);
                    else
                        painter.drawEllipse(center, d_ptr->radiu * 0.7, d_ptr->radiu * 0.7);
                }
                else
                {
                    color = d_ptr->patterneLockState == Setting || d_ptr->patterneLockState == Valid ? QColor("#00FF80") : QColor("#FE4C40");
                    painter.setBrush(color);
                    painter.drawEllipse(center, d_ptr->radiu * 0.7, d_ptr->radiu * 0.7);
                }
            }
            painter.restore();
        }
    }

    if (d_ptr->patterneLockState != NotSet)
    {
        painter.setBrush(Qt::transparent);
        if (d_ptr->patterneLockState == Invalid)
            painter.setPen(QPen(QColor("#FE4C40"),7,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin));
        else
            painter.setPen(QPen(QColor("#00FF80"),7,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin));
        for (int i = 0; i < d_ptr->sets.size() - 1; i++)
            painter.drawLine(d_ptr->circularRects.at(d_ptr->sets.at(i)).center(), d_ptr->circularRects.at(d_ptr->sets.at(i + 1)).center());
        if (d_ptr->patterneLockState == Setting)
            painter.drawLine(d_ptr->circularRects.at(d_ptr->sets.last()).center(), d_ptr->settingMousPos);
    }

    if (mustUpdateCircular)
        d_ptr->isUpdateCircular = false;

}

void HPatternLockWidget::resizeEvent(QResizeEvent *event)
{
    d_ptr->isUpdateCircular = true;
    QWidget::resizeEvent(event);
}

void HPatternLockWidget::mousePressEvent(QMouseEvent *event)
{
    if (d_ptr->lastHoverIndex != -1)
    {
        if (d_ptr->patterneLockState == NotSet)
        {
            d_ptr->patterneLockState = Setting;
            d_ptr->sets << d_ptr->lastHoverIndex;
            d_ptr->circularStates[d_ptr->lastHoverIndex] = Hover;
            d_ptr->settingMousPos = event->pos();
            d_ptr->currentOffset = 0;
            d_ptr->hoverTimer->start();
            update();
        }
    }

    QWidget::mousePressEvent(event);
}

void HPatternLockWidget::mouseMoveEvent(QMouseEvent *event)
{
    auto pos = event->pos();
    int i;
    int currentHoverIndex = -1;
    bool mouseInCircular = false;
    if (d_ptr->patterneLockState == NotSet)
    {
        for (i = 0; i < d_ptr->circularRects.size(); i++)
        {
            if (d_ptr->circularRects.at(i).contains(pos))
            {
                d_ptr->circularStates[i] = Hover;
                currentHoverIndex = i;
                mouseInCircular = true;
            }
            else
            {
                d_ptr->circularStates[i] = Normal;
            }
        }

        if (mouseInCircular)
        {
            d_ptr->lastHoverIndex = currentHoverIndex;
            setCursor(Qt::PointingHandCursor);
        }
        else
        {
            setCursor(Qt::ArrowCursor);
        }

        if (!d_ptr->hoverTimer->isActive())
        {
            if (d_ptr->mouseInCircular != mouseInCircular) //鼠标进入了某个小圆或从小圆出来
            {
                d_ptr->mouseInCircular = mouseInCircular;
                d_ptr->currentOffset = mouseInCircular ? 0 : d_ptr->radiu * 0.2;
                d_ptr->hoverTimer->start();
            }
        }
        update();
    }
    else if(d_ptr->patterneLockState == Setting)
    {
        for (i = 0; i < d_ptr->circularRects.size(); i++)
        {
            if (d_ptr->circularRects.at(i).contains(pos))
            {
                if (!d_ptr->sets.contains(i))
                {
                    d_ptr->sets << i;
                    d_ptr->circularStates[i] = Hover;
                    currentHoverIndex = i;
                }
                mouseInCircular = true;
            }
        }

        if (d_ptr->mouseInCircular != mouseInCircular)
        {
            d_ptr->mouseInCircular = mouseInCircular;
            if (mouseInCircular)
            {
                d_ptr->lastHoverIndex = currentHoverIndex;
                setCursor(Qt::PointingHandCursor);
                if (!d_ptr->hoverTimer->isActive())
                {
                    d_ptr->currentOffset = 0;
                    d_ptr->hoverTimer->start();
                }
            }
            else
                setCursor(Qt::ArrowCursor);
        }
        d_ptr->settingMousPos = pos;
        update();
    }

    QWidget::mouseMoveEvent(event);
}

void HPatternLockWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
    if (d_ptr->patterneLockState == Setting && !d_ptr->mouseInCircular)
    {
        if (d_ptr->sets.size() < 4)
        {
            d_ptr->patterneLockState = Invalid;
            emit passwordChanged("4位以下的无效密码");
        }
        else
        {
            d_ptr->patterneLockState = Valid;
            emit passwordChanged(password());
        }
        update();
    }

    QWidget::mouseDoubleClickEvent(event);

}

void HPatternLockWidget::onHoverTimer()
{
    if (d_ptr->patterneLockState == NotSet)
    {
        if (d_ptr->mouseInCircular)
        {
            if (d_ptr->currentOffset >= d_ptr->radiu * 0.2)
                d_ptr->hoverTimer->stop();
            d_ptr->currentOffset += 2;
        }
        else
        {
            if (d_ptr->currentOffset <= -d_ptr->radiu * 0.1)
                d_ptr->hoverTimer->stop();
            d_ptr->currentOffset -= 2;
        }
    }
    else if (d_ptr->patterneLockState == Setting)
    {
        if (d_ptr->currentOffset >= d_ptr->radiu * 0.1)
            d_ptr->hoverTimer->stop();
        d_ptr->currentOffset += 2;
    }
    update();
}

HE_END_NAMESPACE
