#include "HCalloutChartItem_p.h"
#include <QtGui/QFontMetrics>
#include <QtGui/QPainter>
#include <QtWidgets/QGraphicsSceneMouseEvent>
#include <QtCharts/QChart>

HCalloutChartItem::HCalloutChartItem(QChart *parent) :
    HGraphicsItem(*new HCalloutChartItemPrivate, parent)
{
    Q_D(HCalloutChartItem);
    d->chart = parent;
}

QFont HCalloutChartItem::font()
{
    Q_D(HCalloutChartItem);
    return d->font;
}

void HCalloutChartItem::setFont(const QFont &value)
{
    Q_D(HCalloutChartItem);
    if (d->font == value)
        return;
    d->font = value;
    update();
}

void HCalloutChartItem::setText(const QString &value)
{
    Q_D(HCalloutChartItem);
    QFontMetrics metrics(font());
    d->text = value;
    d->textRect = metrics.boundingRect(0, 0, 150, 150, Qt::AlignLeft, value).translated(5, 5);
    prepareGeometryChange();
    d->rect = d->textRect.adjusted(-5, -5, 5, 5);
}

void HCalloutChartItem::setAnchor(QPointF value)
{
    Q_D(HCalloutChartItem);
    d->anchor = value;
}

void HCalloutChartItem::updateGeometry()
{
    Q_D(HCalloutChartItem);
    prepareGeometryChange();
    setPos(d->chart->mapToPosition(d->anchor) + QPoint(10, -50));
}

QRectF HCalloutChartItem::boundingRect() const
{
    Q_D(const HCalloutChartItem);
    auto anchor = mapFromParent(d->chart->mapToPosition(d->anchor));
    QRectF rect;
    rect.setLeft(qMin(d->rect.left(), anchor.x()));
    rect.setRight(qMax(d->rect.right(), anchor.x()));
    rect.setTop(qMin(d->rect.top(), anchor.y()));
    rect.setBottom(qMax(d->rect.bottom(), anchor.y()));
    return rect;
}

void HCalloutChartItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_D(HCalloutChartItem);
    Q_UNUSED(option)
    Q_UNUSED(widget)
    QPainterPath path;
    path.addRoundedRect(d->rect, 5, 5);
    auto anchor = mapFromParent(d->chart->mapToPosition(d->anchor));
    if (!d->rect.contains(anchor))
    {
        QPointF point1, point2;

        // establish the position of the anchor point in relation to m_rect
        bool above = anchor.y() <= d->rect.top();
        bool aboveCenter = anchor.y() > d->rect.top() && anchor.y() <= d->rect.center().y();
        bool belowCenter = anchor.y() > d->rect.center().y() && anchor.y() <= d->rect.bottom();
        bool below = anchor.y() > d->rect.bottom();

        bool left = anchor.x() <= d->rect.left();
        bool leftCenter = anchor.x() > d->rect.left() && anchor.x() <= d->rect.center().x();
        bool rightCenter = anchor.x() > d->rect.center().x() && anchor.x() <= d->rect.right();
        bool right = anchor.x() > d->rect.right();

        // get the nearest m_rect corner.
        qreal x = (right + rightCenter) * d->rect.width();
        qreal y = (below + belowCenter) * d->rect.height();
        bool cornerCase = (above && left) || (above && right) || (below && left) || (below && right);
        bool vertical = qAbs(anchor.x() - x) > qAbs(anchor.y() - y);

        qreal x1 = x + leftCenter * 10 - rightCenter * 20 + cornerCase * !vertical * (left * 10 - right * 20);
        qreal y1 = y + aboveCenter * 10 - belowCenter * 20 + cornerCase * vertical * (above * 10 - below * 20);;
        point1.setX(x1);
        point1.setY(y1);

        qreal x2 = x + leftCenter * 20 - rightCenter * 10 + cornerCase * !vertical * (left * 20 - right * 10);;
        qreal y2 = y + aboveCenter * 20 - belowCenter * 10 + cornerCase * vertical * (above * 20 - below * 10);;
        point2.setX(x2);
        point2.setY(y2);

        path.moveTo(point1);
        path.lineTo(anchor);
        path.lineTo(point2);
        path = path.simplified();
    }
    painter->setBrush(QColor(255, 255, 255));
    painter->setFont(d->font);
    painter->drawPath(path);
    painter->drawText(d->textRect, d->text);
}

void HCalloutChartItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    event->setAccepted(true);
}

void HCalloutChartItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton)
    {
        setPos(mapToParent(event->pos() - event->buttonDownPos(Qt::LeftButton)));
        event->setAccepted(true);
    }
    else
        event->setAccepted(false);
}
