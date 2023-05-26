#include "HGraphicsObject_p.h"
#include "HGraphicsHelper.h"
#include <QtGui/QPainter>
#include <QtWidgets/QGraphicsSceneEvent>
#include <QtWidgets/QStyleOptionGraphicsItem>

HE_BEGIN_NAMESPACE

HGraphicsObject::HGraphicsObject(QGraphicsItem *parent) :
    QGraphicsObject(parent),
    d_ptr(new HGraphicsObjectPrivate)
{
    init();
}

HGraphicsObject::HGraphicsObject(HGraphicsObjectPrivate &p, QGraphicsItem *parent) :
    QGraphicsObject(parent),
    d_ptr(&p)
{
}

HGraphicsObject::~HGraphicsObject()
{
}

QRectF HGraphicsObject::boundingRect() const
{
    return  QRectF(0, 0, d_ptr->itemSize.width() + 10, d_ptr->itemSize.height() + 10);
}

HGraphicsObject::ItemFix HGraphicsObject::itemFix() const
{
    return d_ptr->itemFix;
}

void HGraphicsObject::setItemFix(ItemFix value)
{
    d_ptr->itemFix = value;
}

QVariant HGraphicsObject::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if ((change == ItemPositionChange || change == ItemPositionHasChanged) && scene())
    {
        QVariant pos;
        if (d_ptr->itemFix == FixByScene)
            pos = HGraphicsHelper::fixByScene(this, value);
        else if (d_ptr->itemFix == FixByOverlap)
            pos = HGraphicsHelper::fixByOverlap(this, value);
        if (pos.isValid())
            return pos;
    }
    return QGraphicsItem::itemChange(change, value);
}

void HGraphicsObject::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        if (isInResizeArea(event->pos()))
            d_ptr->resizing = true;
    }
    QGraphicsObject::mousePressEvent(event);
}

void HGraphicsObject::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (d_ptr->resizing)
    {
        auto w = event->pos().x();
        auto h = event->pos().y();
        if (w >= d_ptr->minimumSizeHint.width())
            d_ptr->itemSize.setWidth(w);
        if (h >= d_ptr->minimumSizeHint.height())
            d_ptr->itemSize.setHeight(h);
        prepareGeometryChange();
    }
    else
        QGraphicsObject::mouseMoveEvent(event);
}

void HGraphicsObject::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && d_ptr->resizing)
        d_ptr->resizing = false;
    QGraphicsObject::mouseReleaseEvent(event);
}

void HGraphicsObject::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    if (d_ptr->resizing || (isInResizeArea(event->pos()) && isSelected()))
        setCursor(Qt::SizeFDiagCursor);
    else
        setCursor(Qt::ArrowCursor);
    QGraphicsObject::hoverMoveEvent(event);
}

void HGraphicsObject::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget */*widget*/)
{
    painter->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform | QPainter::TextAntialiasing);
    drawBound(painter, option);
    drawContent(painter, option);
    drawResizeArea(painter, option);
}

void HGraphicsObject::init()
{
    setAcceptHoverEvents(true);
    setZValue(1);
    setFlags(ItemIsMovable | ItemSendsScenePositionChanges | ItemIsSelectable | ItemIsFocusable);
}

bool HGraphicsObject::isInResizeArea(const QPointF &pos)
{
    return (pos.x() - d_ptr->itemSize.width() + d_ptr->resizePos[0]) > (d_ptr->itemSize.height() - pos.y());
}

void HGraphicsObject::drawBound(QPainter *painter, const QStyleOptionGraphicsItem *option)
{
    auto rect = boundingRect();
    painter->save();
    if (option->state & QStyle::State_Selected)
    {
        painter->setPen(QPen(Qt::black, 1, Qt::DashLine));
        painter->drawRect(rect);
        setZValue(2);
    }
    else
    {
        setZValue(1);
        painter->fillRect(rect, QBrush(Qt::transparent));
    }
    painter->restore();
}

void HGraphicsObject::drawResizeArea(QPainter *painter, const QStyleOptionGraphicsItem *option)
{
    if (option->state & QStyle::State_Selected)
    {
        painter->save();
        auto w = int(boundingRect().width());
        auto h = int(boundingRect().height());
        painter->setPen(Qt::red);
        for (auto p : d_ptr->resizePos)
            painter->drawLine(w - p, h, w, h - p);
        painter->restore();
    }
}

HE_END_NAMESPACE
