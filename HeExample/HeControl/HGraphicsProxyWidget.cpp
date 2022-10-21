#include "HGraphicsProxyWidget_p.h"
#include "HGraphicsHelper.h"
#include <QtGui/QPainter>
#include <QtWidgets/QGraphicsScene>
#include <QtWidgets/QGraphicsSceneEvent>
#include <QtWidgets/QStyleOptionGraphicsItem>

HE_BEGIN_NAMESPACE

HGraphicsProxyWidget::HGraphicsProxyWidget(QGraphicsItem *parent) :
    QGraphicsProxyWidget(parent),
    d_ptr(new HGraphicsProxyWidgetPrivate)
{
    init();
}

HGraphicsProxyWidget::HGraphicsProxyWidget(HGraphicsProxyWidgetPrivate &p, QGraphicsItem *parent) :
    QGraphicsProxyWidget(parent),
    d_ptr(&p)
{
}

HGraphicsProxyWidget::~HGraphicsProxyWidget()
{
}

QRectF HGraphicsProxyWidget::boundingRect() const
{
    return  QRectF(0, 0, d_ptr->itemSize.width() + 5, d_ptr->itemSize.height() + 5);
}

void HGraphicsProxyWidget::setCenterWidget(QWidget *w)
{
    setWidget(w);
    d_ptr->itemSize = w->sizeHint();
    d_ptr->minimumSizeHint = w->minimumSize();
    update();
}

QVariant HGraphicsProxyWidget::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    if ((change == ItemPositionChange || change == ItemPositionHasChanged) && scene())
    {
        auto pos = HGraphicsHelper::fixByScene(this, value);
        if (pos.isValid())
            return pos;
    }
    return QGraphicsItem::itemChange(change, value);
}

void HGraphicsProxyWidget::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->save();
    painter->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform | QPainter::TextAntialiasing);
    if (option->state & QStyle::State_Selected)
    {
        auto w = boundingRect().width();
        auto h = boundingRect().height();
        painter->setPen(Qt::red);
        for (auto p : d_ptr->resizePos)
            painter->drawLine(w - p, h, w, h - p);
    }
    painter->restore();
    QGraphicsProxyWidget::paint(painter,option, widget);
}

void HGraphicsProxyWidget::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        auto pos = event->pos();
        if (isInResizeArea(pos))
        {
            d_ptr->resizing = true;
        }
        else
        {
            d_ptr->grabbedByWidget = widget()->childAt(pos.toPoint());
            if (d_ptr->grabbedByWidget)
                QGraphicsProxyWidget::mousePressEvent(event);
            else
                QGraphicsItem::mousePressEvent(event);
        }
    }
}

void HGraphicsProxyWidget::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (d_ptr->resizing)
    {
        auto w = event->pos().x();
        auto h = event->pos().y();
        if (w >= d_ptr->minimumSizeHint.width())
            d_ptr->itemSize.setWidth(w);
        if (h >= d_ptr->minimumSizeHint.height())
            d_ptr->itemSize.setHeight(h);
        resize(w ,h);
        prepareGeometryChange();
    }
    else
    {
        if (d_ptr->grabbedByWidget)
            return;
        QGraphicsItem::mouseMoveEvent(event);
    }
}

void HGraphicsProxyWidget::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && d_ptr->resizing)
        d_ptr->resizing = false;
    else
    {
        if (d_ptr->grabbedByWidget)
            QGraphicsProxyWidget::mouseReleaseEvent(event);
        else
            QGraphicsItem::mouseReleaseEvent(event);
    }
    d_ptr->grabbedByWidget = false;
}

void HGraphicsProxyWidget::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    d_ptr->grabbedByWidget = widget()->childAt(event->pos().toPoint());
    if (d_ptr->grabbedByWidget)
        QGraphicsProxyWidget::mouseDoubleClickEvent(event);
    else
        QGraphicsItem::mouseDoubleClickEvent(event);
}

void HGraphicsProxyWidget::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    if (d_ptr->resizing || (isInResizeArea(event->pos()) && isSelected()))
    {
        setCursor(Qt::SizeFDiagCursor);
        QGraphicsObject::hoverMoveEvent(event);
    }
    else
    {
        auto w = widget()->childAt(event->pos().toPoint());
        if (w)
            setCursor(w->cursor());
        else
            setCursor(Qt::ArrowCursor);
        QGraphicsProxyWidget::hoverMoveEvent(event);
    }
}

void HGraphicsProxyWidget::init()
{
    setAcceptHoverEvents(true);
    setZValue(1);
    setFlags(ItemIsMovable | ItemSendsScenePositionChanges | ItemIsSelectable | ItemIsFocusable);
}

bool HGraphicsProxyWidget::isInResizeArea(const QPointF &pos)
{
    return (pos.x() - d_ptr->itemSize.width() + d_ptr->resizePos[0]) > (d_ptr->itemSize.height() - pos.y());
}

HE_END_NAMESPACE
