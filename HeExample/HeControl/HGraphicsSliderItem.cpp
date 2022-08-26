#include "HGraphicsSliderItem_p.h"
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
    if (d->slidePressed )
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

void HGraphicsSliderItem::init()
{
    HGraphicsObject::init();
    setZValue(1);
}

void HGraphicsSliderItem::drawItem(QPainter *painter, const QStyleOptionGraphicsItem *option)
{

}



HE_END_NAMESPACE

void sliderGraphicsPixmapItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    painter->save();
    painter->setRenderHint(QPainter::Antialiasing);

    QRectF thisRectF = boundingRect();
    if(option->state & QStyle::State_Selected)
    {
        painter->setPen(QColor("#D8D8D8"));
        painter->drawRect(thisRectF);
        setZValue(2);
    }
    else
    {
        setZValue(1);
        painter->fillRect(thisRectF, QBrush(Qt::transparent));
    }

    QRect rect = thisRectF.toRect();
    painter->save();
    painter->setPen(Qt::transparent);
    if(sliderOrientation == Qt::Horizontal)
    {
        QRect sliderRect = QRect(5,(rect.height() - 12) / 2,rect.width() - 10,12);
        painter->save();
        QColor slightlyOpaqueBlack(0, 0, 0, 63);
        painter->setBrush(slightlyOpaqueBlack);
        painter->drawRect(sliderRect);
        painter->restore();

        painter->save();
        painter->setBrush(QColor("#00beac"));
        int nowValueWidth = static_cast<int>(static_cast<float>(sliderRect.width() * (nowValue - minValue))  / static_cast<float>(maxValue - minValue));
        sliderRect.setWidth(nowValueWidth);
        painter->drawRoundRect(sliderRect);

        int thisSliderRectX = nowValueWidth + 5;
        if(thisSliderRectX < 5)
            thisSliderRectX = 5;
        if(thisSliderRectX > (5 + rect.width() - 20))
            thisSliderRectX = 5 + rect.width() - 20 - 10;

        thisSliderRect = QRect(thisSliderRectX,sliderRect.y() - 4,20,20);

        if(pressThisSlider || inThisSliderRect)
            painter->setBrush(QColor("#01968c"));
        painter->drawEllipse(thisSliderRect);
        painter->restore();
    }
    else
    {
        QRect sliderRect = QRect((rect.width() - 12) / 2,5,12,rect.height() - 10);
        painter->save();
        QColor slightlyOpaqueBlack(0, 0, 0, 63);
        painter->setBrush(slightlyOpaqueBlack);
        painter->drawRect(sliderRect);
        painter->restore();
        painter->save();
        painter->setBrush(QColor("#00beac"));
        int nowValueHeight = static_cast<int>(static_cast<float>(sliderRect.height() * (nowValue - minValue))  / static_cast<float>(maxValue - minValue));
        sliderRect.setHeight(nowValueHeight);
        painter->drawRoundRect(sliderRect);

        int thisSliderRectY = nowValueHeight + 5;
        if(thisSliderRectY < 5)
            thisSliderRectY = 5;
        if(thisSliderRectY > (5 + rect.height() - 20))
            thisSliderRectY = 5 + rect.height() - 20 - 10;

        thisSliderRect = QRect(sliderRect.x() - 4,thisSliderRectY,20,20);

        if(pressThisSlider || inThisSliderRect)
            painter->setBrush(QColor("#01968c"));
        painter->drawEllipse(thisSliderRect);
        painter->restore();
    }
    painter->restore();

    if(option->state & QStyle::State_Selected)
    {
        qreal w = thisRectF.width();
        qreal h = thisRectF.height();
        painter->setPen(Qt::red);
        for (int i = 0; i < 3; ++i)//三角形
            painter->drawLine(static_cast<int>(w - g_cResizePos[i]) , static_cast<int>(h), static_cast<int>(w), static_cast<int>(h - g_cResizePos[i]));
    }

    painter->restore();
}

void sliderGraphicsPixmapItem::hoverMoveEvent(QGraphicsSceneHoverEvent* event)
{
    QPointF point = event->pos();

    if (isResizing || (IsInResizeArea(point) && isSelected()))
        setCursor(Qt::SizeFDiagCursor);
    else
        setCursor(Qt::ArrowCursor);

    if(thisSliderRect.contains(point.x(),point.y()))
    {
        inThisSliderRect = true;
    }
    else
    {
        inThisSliderRect = false;
    }
    update();

    QGraphicsObject::hoverMoveEvent(event);
}

