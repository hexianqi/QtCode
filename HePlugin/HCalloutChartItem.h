/***************************************************************************************************
**      2019-04-03  HGraphicsCalloutItem    标注图样项。
***************************************************************************************************/

#ifndef HCALLOUTCHARTITEM_H
#define HCALLOUTCHARTITEM_H

#include "HGraphicsItem.h"
#include <QtCharts/QChartGlobal>

QT_CHARTS_BEGIN_NAMESPACE
class QChart;
QT_CHARTS_END_NAMESPACE
QT_CHARTS_USE_NAMESPACE

class QGraphicsSceneMouseEvent;
class HCalloutChartItemPrivate;

class QDESIGNER_WIDGET_EXPORT HCalloutChartItem : public HGraphicsItem
{
    Q_DECLARE_PRIVATE(HCalloutChartItem)

public:
    explicit HCalloutChartItem(QChart *parent = nullptr);

public:
    QFont font();

public:
    void setFont(QFont value);
    void setText(QString value);
    void setAnchor(QPointF value);
    void updateGeometry();

public:
    QRectF boundingRect() const override;
    void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *) override;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *) override;
};

#endif // HCALLOUTCHARTITEM_H
