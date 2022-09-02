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

//    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)override;


//    void hoverMoveEvent(QGraphicsSceneHoverEvent* event)override;
//    void mouseMoveEvent(QGraphicsSceneMouseEvent* event)override;
//    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event)override;
//private:
//    QRectF drawRect;//整个大圆的范围
//    bool isPointInCir(const QPoint &point, const QRect & rect);
//    QPainterPath fanShaped[4];
//    QRectF centerCircularRect;//中心圆按钮的范围
//    QPainterPath gradientArc(double startAngle, double angleLength, double arcHeight);
//    enum class pressBtnType //按下的是哪个按钮
//    {
//        up = 0,
//        left,
//        down,
//        right,
//        center,
//        None
//    };
//    pressBtnType pressedBtn{pressBtnType::None};
//};

//#endif // DISCBUTTONGRAPHICSPIXMAPITEM_H

