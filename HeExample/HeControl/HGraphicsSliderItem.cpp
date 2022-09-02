#include "HGraphicsSliderItem_p.h"
#include <QtGui/QPainter>
#include <QtWidgets/QGraphicsSceneEvent>

HE_BEGIN_NAMESPACE

HGraphicsSliderItemPrivate::HGraphicsSliderItemPrivate(Qt::Orientation orientation)
{
    this->orientation = orientation;
    this->itemSize = QSizeF(250, 80);
}

HGraphicsSliderItem::HGraphicsSliderItem(Qt::Orientation orientation, QGraphicsItem *parent) :
    HGraphicsObject(*new HGraphicsSliderItemPrivate(orientation), parent)
{
    init();
}

HGraphicsSliderItem::HGraphicsSliderItem(HGraphicsSliderItemPrivate &p, QGraphicsItem *parent) :
    HGraphicsObject(p, parent)
{
}

HGraphicsSliderItem::~HGraphicsSliderItem()
{
}

int HGraphicsSliderItem::type() const
{
    return Type;
}

void HGraphicsSliderItem::setOrientation(Qt::Orientation value)
{
    Q_D(HGraphicsSliderItem);
    if (d->orientation == value)
        return;
    d->orientation = value;
    update();
}

void HGraphicsSliderItem::setRange(const int min, const int max)
{
    Q_D(HGraphicsSliderItem);
    d->minValue = qMin(min, max);
    d->maxValue = qMax(min, max);
    update();
}

void HGraphicsSliderItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_D(HGraphicsSliderItem);
    if (event->button() == Qt::LeftButton)
    {
        if (d->sliderRect.contains(event->pos()))
        {
            d->slidePressed = true;
            setFlag(QGraphicsItem::ItemIsMovable, false);
        }
        else
        {
            d->slidePressed = false;
            setFlag(QGraphicsItem::ItemIsMovable, true);
        }
    }
    HGraphicsObject::mousePressEvent(event);
}

void HGraphicsSliderItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    Q_D(HGraphicsSliderItem);
    if (d->slidePressed)
    {
        auto range = d->maxValue - d->minValue;
        auto temp = 0;
        if (d->orientation == Qt::Horizontal)
            temp = (event->pos().x() - 5) * range / (boundingRect().width() - 10.0);
        else
            temp = (event->pos().y() - 5) * range / (boundingRect().height() - 10.0);
        temp = qBound(0, temp, range);
        d->nowValue = temp + d->minValue;
        update();
    }
    HGraphicsObject::mouseMoveEvent(event);
}

void HGraphicsSliderItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    Q_D(HGraphicsSliderItem);
    if (d->slidePressed)
        d->slidePressed = false;
    HGraphicsObject::mouseReleaseEvent(event);
}

void HGraphicsSliderItem::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    Q_D(HGraphicsSliderItem);
    auto point = event->pos();
    d->inSliderRect = d->sliderRect.contains(point);
    HGraphicsObject::hoverMoveEvent(event);
}

void HGraphicsSliderItem::drawContent(QPainter *painter, const QStyleOptionGraphicsItem */*option*/)
{
    Q_D(HGraphicsSliderItem);
    auto rect = boundingRect().toRect();
    painter->save();
    painter->setPen(Qt::transparent);
    if (d->orientation == Qt::Horizontal)
    {
        auto sliderRect = QRect(5, (rect.height() - 12) / 2, rect.width() - 10, 12);
        int width = 1.0 * sliderRect.width() * (d->nowValue - d->minValue)  / (d->maxValue - d->minValue);
        int x = qBound(5, width - 5, rect.width() - 25);
        painter->setBrush(QColor("#0000003F"));
        painter->drawRect(sliderRect);
        painter->setBrush(QColor("#00beac"));
        sliderRect.setWidth(width);
        painter->drawRoundRect(sliderRect);
        d->sliderRect = QRect(x, sliderRect.y() - 4, 20, 20);
    }
    else
    {
        auto sliderRect = QRect((rect.width() - 12) / 2, 5, 12, rect.height() - 10);
        int height = 1.0 * sliderRect.height() * (d->nowValue - d->minValue)  / (d->maxValue - d->minValue);
        int y = qBound(5, height - 5, rect.width() - 25);
        painter->setBrush(QColor("#0000003F"));
        painter->drawRect(sliderRect);
        painter->setBrush(QColor("#00beac"));
        sliderRect.setHeight(height);
        painter->drawRoundRect(sliderRect);
        d->sliderRect = QRect(sliderRect.x() - 4, y, 20, 20);
    }
    if (d->slidePressed || d->inSliderRect)
        painter->setBrush(QColor("#01968c"));
    painter->drawEllipse(d->sliderRect);
    painter->restore();
}

HE_END_NAMESPACE

