/***************************************************************************************************
**      2022-08-31  HGraphicsDiscButtonItem
***************************************************************************************************/

#pragma once

#include "HGraphicsObject.h"

HE_BEGIN_NAMESPACE

class HGraphicsDiscButtonItemPrivate;

class HGraphicsDiscButtonItem : public HGraphicsObject
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HGraphicsDiscButtonItem)

    enum ButtonType
    {
        Button_Up = 0,
        Button_Left,
        Button_Down,
        Button_Right,
        Button_Center,
        Button_None
    };

public:
    explicit HGraphicsDiscButtonItem(QGraphicsItem *parent = nullptr);
    ~HGraphicsDiscButtonItem() override;

public:
    enum { Type = UserType + 26 };
    int type() const override;

protected:
    HGraphicsDiscButtonItem(HGraphicsDiscButtonItemPrivate &p, QGraphicsItem *parent = nullptr);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *) override;
    void drawContent(QPainter *painter, const QStyleOptionGraphicsItem *option) override;
    bool isInBoard(const QPointF &);
    bool isInCircular(const QPointF &);
    double radius(const QPointF &);
    QPainterPath gradientArc(double startAngle, double angleLength);
};

HE_END_NAMESPACE
