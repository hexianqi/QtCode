/***************************************************************************************************
**      2022-08-26  HGraphicsSliderItem
***************************************************************************************************/

#pragma once

#include "HGraphicsObject.h"

HE_BEGIN_NAMESPACE

class HGraphicsSliderItemPrivate;

class HGraphicsSliderItem : public HGraphicsObject
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HGraphicsSliderItem)

public:
    explicit HGraphicsSliderItem(Qt::Orientation orientation, QGraphicsItem *parent = nullptr);
    ~HGraphicsSliderItem() override;

public:
    void setOrientation(Qt::Orientation);
    void setRange(const int min, const int max);

protected:
    HGraphicsSliderItem(HGraphicsSliderItemPrivate &p, QGraphicsItem *parent = nullptr);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *) override;
    void hoverMoveEvent(QGraphicsSceneHoverEvent *) override;
    void init() override;
    void drawItem(QPainter *painter, const QStyleOptionGraphicsItem *option) override;

};

HE_END_NAMESPACE
