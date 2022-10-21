/***************************************************************************************************
**      2022-10-19  HGraphicsProxyWidget
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include <QtWidgets/QGraphicsProxyWidget>

HE_BEGIN_NAMESPACE

class HGraphicsProxyWidgetPrivate;

class HGraphicsProxyWidget : public QGraphicsProxyWidget
{
    Q_OBJECT

public:
    explicit HGraphicsProxyWidget(QGraphicsItem *parent = nullptr);
    ~HGraphicsProxyWidget() override;

public:
    QRectF boundingRect()const override;

public:
    void setCenterWidget(QWidget *);

protected:
    HGraphicsProxyWidget(HGraphicsProxyWidgetPrivate &p, QGraphicsItem *parent = nullptr);

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
    void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *) override;
    void hoverMoveEvent(QGraphicsSceneHoverEvent *) override;
    virtual void init();
    virtual bool isInResizeArea(const QPointF& pos);

protected:
    QScopedPointer<HGraphicsProxyWidgetPrivate> d_ptr;
};

HE_END_NAMESPACE
