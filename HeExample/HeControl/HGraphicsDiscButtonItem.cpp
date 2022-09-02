#include "HGraphicsDiscButtonItem_p.h"
#include <QtGui/QPainter>
#include <QtWidgets/QGraphicsSceneEvent>

HE_BEGIN_NAMESPACE

HGraphicsDiscButtonItemPrivate::HGraphicsDiscButtonItemPrivate()
{
    itemSize = QSizeF(100, 100);
    minimumSizeHint = QSizeF(100, 100);
}

HGraphicsDiscButtonItem::HGraphicsDiscButtonItem(QGraphicsItem *parent) :
    HGraphicsObject(*new HGraphicsDiscButtonItemPrivate, parent)
{
    init();
}

HGraphicsDiscButtonItem::HGraphicsDiscButtonItem(HGraphicsDiscButtonItemPrivate &p, QGraphicsItem *parent) :
    HGraphicsObject(p, parent)
{
}

HGraphicsDiscButtonItem::~HGraphicsDiscButtonItem()
{
}

int HGraphicsDiscButtonItem::type() const
{
    return Type;
}

void HGraphicsDiscButtonItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_D(HGraphicsDiscButtonItem);
    if (event->button() == Qt::LeftButton)
    {
        auto pos = event->pos();
        if (isInBoard(pos))
        {
            if (isInCircular(pos))
            {
                d->pressButtonType = Button_Center;
            }
            else
            {
                auto line = QLineF(d->boardCenter, pos);
                auto angle = line.angle();
                if (angle < 45.0 || angle >= 315.0)
                    d->pressButtonType = Button_Right;
                else if (angle >= 45.0 && angle < 135.0)
                    d->pressButtonType = Button_Up;
                else if (angle >= 135.0 && angle < 225.0)
                    d->pressButtonType = Button_Left;
                else if (angle >= 225.0 && angle < 315.0)
                    d->pressButtonType = Button_Down;
            }
            update();
        }
    }
    HGraphicsObject::mousePressEvent(event);
}

void HGraphicsDiscButtonItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    Q_D(HGraphicsDiscButtonItem);
    if (event->button() == Qt::LeftButton)
    {
        if (d->pressButtonType != Button_None)
        {
            d->pressButtonType = Button_None;
            update();
        }
    }
    HGraphicsObject::mouseReleaseEvent(event);
}

void HGraphicsDiscButtonItem::drawContent(QPainter *painter, const QStyleOptionGraphicsItem */*option*/)
{
    Q_D(HGraphicsDiscButtonItem);
    QPainterPath fanShaped[4];
    auto rect = boundingRect();
    auto font = painter->font();
    font.setPixelSize(24);
    d->boardCenter = rect.center();
    d->boardRadius = qMin(rect.width(), rect.height()) / 2 - 10;
    d->circularRadius = d->boardRadius / 2 - 2;
    auto boardRect = QRectF(d->boardCenter.x() - d->boardRadius, d->boardCenter.y() - d->boardRadius, 2 * d->boardRadius, 2 * d->boardRadius);
    auto circularRect = QRectF(d->boardCenter.x() - d->circularRadius, d->boardCenter.y() - d->circularRadius, 2 * d->circularRadius, 2 * d->circularRadius);
    fanShaped[0] = gradientArc(45.0,  90.0); // 上
    fanShaped[1] = gradientArc(135.0, 90.0); // 左
    fanShaped[2] = gradientArc(225.0, 90.0); // 下
    fanShaped[3] = gradientArc(315.0, 90.0); // 右
    painter->save();
    painter->setPen(QColor("#222222"));
    painter->setBrush(QColor("#EAEAEA"));
    for (int i = 0;i < 4; i++)
        painter->drawPath(fanShaped[i]);
    painter->setPen(Qt::transparent);
    painter->drawEllipse(circularRect);
    painter->setFont(font);
    painter->setPen(QPen(QColor("#000000"), 2));
    painter->drawText(boardRect.left(), circularRect.top(), d->boardRadius - d->circularRadius, d->circularRadius * 2, Qt::AlignCenter, "〈");
    painter->drawText(circularRect.right(), circularRect.top(), d->boardRadius - d->circularRadius, d->circularRadius * 2, Qt::AlignCenter, "〉");
    painter->drawText(circularRect.left(), boardRect.top(), d->circularRadius * 2, d->boardRadius - d->circularRadius, Qt::AlignCenter, "︿");
    painter->drawText(circularRect.left(), circularRect.bottom(), d->circularRadius * 2, d->boardRadius - d->circularRadius, Qt::AlignCenter, "﹀");
    painter->drawText(circularRect, Qt::AlignCenter, "OK");
    if (d->pressButtonType != Button_None)
    {
        painter->setBrush(QColor("#3F000000"));
        painter->setPen(Qt::transparent);
        if (d->pressButtonType == Button_Center)
        {
            painter->drawEllipse(circularRect);
        }
        else
        {
            auto index =  static_cast<int>(d->pressButtonType);
            if (index >= 0)
                painter->drawPath(fanShaped[index]);
        }
    }
    painter->restore();
}

bool HGraphicsDiscButtonItem::isInBoard(const QPointF &point)
{
    Q_D(HGraphicsDiscButtonItem);
    return radius(point) <= d->boardRadius;
}

bool HGraphicsDiscButtonItem::isInCircular(const QPointF &point)
{
    Q_D(HGraphicsDiscButtonItem);
    return radius(point) <= d->circularRadius;
}

double HGraphicsDiscButtonItem::radius(const QPointF &point)
{
    Q_D(HGraphicsDiscButtonItem);
    auto p = point - d->boardCenter;
    return sqrt(p.x() * p.x() + p.y() * p.y());
}

QPainterPath HGraphicsDiscButtonItem::gradientArc(double startAngle, double angleLength)
{
    Q_D(HGraphicsDiscButtonItem);
    QPainterPath arcPath, ellipsePath;
    arcPath.moveTo(d->boardCenter);
    arcPath.arcTo(d->boardCenter.x() - d->boardRadius, d->boardCenter.y() - d->boardRadius, 2 * d->boardRadius, 2 * d->boardRadius, startAngle, angleLength);
    ellipsePath.addEllipse(d->boardCenter, d->boardRadius / 2, d->boardRadius / 2);
    return arcPath - ellipsePath;
}

HE_END_NAMESPACE


