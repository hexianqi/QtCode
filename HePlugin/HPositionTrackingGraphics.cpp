#include "HPositionTrackingGraphics.h"

HPositionTrackingGraphics::HPositionTrackingGraphics(QGraphicsItem *parent)
    : QGraphicsSimpleTextItem(parent)
{
    setZValue(100);
}

void HPositionTrackingGraphics::setValidRegion(QRectF value)
{
    setPos(value.left() + 10, value.top() + 10);
}

void HPositionTrackingGraphics::setVisible(bool b)
{
    QGraphicsSimpleTextItem::setVisible(b);
}

void HPositionTrackingGraphics::setText(QString text)
{
    QGraphicsSimpleTextItem::setText(text);
}
