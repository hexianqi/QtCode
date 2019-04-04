/***************************************************************************************************
**      2019-04-03  HGraphicsCalloutItem    标注图样项。
***************************************************************************************************/

#ifndef HGRAPHICSCALLOUTITEM_H
#define HGRAPHICSCALLOUTITEM_H

#include "HGraphicsItem.h"
#include <QtCharts/QChartGlobal>

QT_CHARTS_BEGIN_NAMESPACE
class QChart;
QT_CHARTS_END_NAMESPACE
QT_CHARTS_USE_NAMESPACE

class QGraphicsSceneMouseEvent;
class HGraphicsCalloutItemPrivate;

class QDESIGNER_WIDGET_EXPORT HGraphicsCalloutItem : public HGraphicsItem
{
    Q_DECLARE_PRIVATE(HGraphicsCalloutItem)

public:
    explicit HGraphicsCalloutItem(QChart *parent = nullptr);
    ~HGraphicsCalloutItem() override;

public:
    void setFont(QFont value);
    void setText(QString value);
    void setAnchor(QPointF value);
    void updateGeometry();
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

public:
    QFont font();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *) override;
};

#endif // HGRAPHICSCALLOUTITEM_H
