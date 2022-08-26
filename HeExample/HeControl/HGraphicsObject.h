/***************************************************************************************************
**      2022-08-26  HGraphicsObject
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include <QtWidgets/QGraphicsObject>

HE_BEGIN_NAMESPACE

class HGraphicsObjectPrivate;

class HGraphicsObject : public QGraphicsObject
{
    Q_OBJECT

public:
    explicit HGraphicsObject(QGraphicsItem *parent = nullptr);
    ~HGraphicsObject() override;

public:
    QRectF boundingRect()const override;

protected:
    HGraphicsObject(HGraphicsObjectPrivate &p, QGraphicsItem *parent = nullptr);

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *) override;
    void hoverMoveEvent(QGraphicsSceneHoverEvent *) override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    virtual bool isInResizeArea(const QPointF &);
    virtual void init();
    virtual void drawBound(QPainter *painter, const QStyleOptionGraphicsItem *option);
    virtual void drawItem(QPainter *painter, const QStyleOptionGraphicsItem *option) = 0;
    virtual void drawResizeArea(QPainter *painter, const QStyleOptionGraphicsItem *option);

protected:
    QScopedPointer<HGraphicsObjectPrivate> d_ptr;
};

HE_END_NAMESPACE

