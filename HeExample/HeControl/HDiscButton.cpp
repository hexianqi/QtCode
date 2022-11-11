#include "HDiscButton_p.h"
#include <QtGui/QtEvents>
#include <QtGui/QPainter>

HE_BEGIN_NAMESPACE

HDiscButton::HDiscButton(QWidget *parent) :
    QWidget(parent),
    d_ptr(new HDiscButtonPrivate)
{
}

HDiscButton::~HDiscButton()
{
}

void HDiscButton::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPainterPath fanShaped[4];
    d_ptr->boardCenter = rect().center();
    d_ptr->boardRadius = qMin(width(), height()) / 2 - 10;
    d_ptr->circularRadius = d_ptr->boardRadius / 2 - 2;
    auto boardRect = QRectF(d_ptr->boardCenter.x() - d_ptr->boardRadius, d_ptr->boardCenter.y() - d_ptr->boardRadius, 2 * d_ptr->boardRadius, 2 * d_ptr->boardRadius);
    auto circularRect = QRectF(d_ptr->boardCenter.x() - d_ptr->circularRadius, d_ptr->boardCenter.y() - d_ptr->circularRadius, 2 * d_ptr->circularRadius, 2 * d_ptr->circularRadius);
    auto font = painter.font();
    font.setPixelSize(24);
    fanShaped[0] = gradientArc(45.0,  90.0); // 上
    fanShaped[1] = gradientArc(135.0, 90.0); // 左
    fanShaped[2] = gradientArc(225.0, 90.0); // 下
    fanShaped[3] = gradientArc(315.0, 90.0); // 右

    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    painter.save();
    painter.setPen(QColor("#222222"));
    painter.setBrush(QColor("#EAEAEA"));
    for (int i = 0 ;i < 4; i++)
        painter.drawPath(fanShaped[i]);
    painter.setPen(Qt::transparent);
    painter.drawEllipse(circularRect);

    painter.setFont(font);
    painter.setPen(QPen(QColor("#000000"), 2));
    painter.drawText(boardRect.left(), circularRect.top(), d_ptr->boardRadius - d_ptr->circularRadius, d_ptr->circularRadius * 2, Qt::AlignCenter, "〈");
    painter.drawText(circularRect.right(), circularRect.top(), d_ptr->boardRadius - d_ptr->circularRadius, d_ptr->circularRadius * 2, Qt::AlignCenter, "〉");
    painter.drawText(circularRect.left(), boardRect.top(), d_ptr->circularRadius * 2, d_ptr->boardRadius - d_ptr->circularRadius, Qt::AlignCenter, "︿");
    painter.drawText(circularRect.left(), circularRect.bottom(), d_ptr->circularRadius * 2, d_ptr->boardRadius - d_ptr->circularRadius, Qt::AlignCenter, "﹀");
    painter.drawText(circularRect, Qt::AlignCenter, "OK");
    if (d_ptr->pressButtonType != Button_None)
    {
        painter.setBrush(QColor("#3F000000"));
        painter.setPen(Qt::transparent);
        if (d_ptr->pressButtonType == Button_Center)
        {
            painter.drawEllipse(circularRect);
        }
        else
        {
            auto index =  static_cast<int>(d_ptr->pressButtonType);
            if (index >= 0)
                painter.drawPath(fanShaped[index]);
        }
    }
    painter.restore();
}

void HDiscButton::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        auto pos = event->pos();
        if (isInBoard(pos))
        {
            if (isInCircular(pos))
            {
                d_ptr->pressButtonType = Button_Center;
            }
            else
            {
                auto line = QLineF(d_ptr->boardCenter, pos);
                auto angle = line.angle();
                if (angle < 45.0 || angle >= 315.0)
                    d_ptr->pressButtonType = Button_Right;
                else if (angle >= 45.0 && angle < 135.0)
                    d_ptr->pressButtonType = Button_Up;
                else if (angle >= 135.0 && angle < 225.0)
                    d_ptr->pressButtonType = Button_Left;
                else if (angle >= 225.0 && angle < 315.0)
                    d_ptr->pressButtonType = Button_Down;
            }
            update();
        }
    }
    return QWidget::mousePressEvent(event);
}

void HDiscButton::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        if (d_ptr->pressButtonType != Button_None)
        {
            d_ptr->pressButtonType = Button_None;
            update();
        }
    }
    return QWidget::mouseReleaseEvent(event);
}

bool HDiscButton::isInBoard(const QPointF &point)
{
    return radius(point) <= d_ptr->boardRadius;
}

bool HDiscButton::isInCircular(const QPointF &point)
{
    return radius(point) <= d_ptr->circularRadius;
}

double HDiscButton::radius(const QPointF &point)
{
    auto p = point - d_ptr->boardCenter;
    return sqrt(p.x() * p.x() + p.y() * p.y());
}

QPainterPath HDiscButton::gradientArc(double startAngle, double angleLength)
{
    QPainterPath arcPath, ellipsePath;
    arcPath.moveTo(d_ptr->boardCenter);
    arcPath.arcTo(d_ptr->boardCenter.x() - d_ptr->boardRadius, d_ptr->boardCenter.y() - d_ptr->boardRadius, 2 * d_ptr->boardRadius, 2 * d_ptr->boardRadius, startAngle, angleLength);
    ellipsePath.addEllipse(d_ptr->boardCenter, d_ptr->boardRadius / 2, d_ptr->boardRadius / 2);
    return arcPath - ellipsePath;
}

HE_END_NAMESPACE

