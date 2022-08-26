/***************************************************************************************************
**      2022-08-26  HGraphicsPixmapItem 拖拽图形项改变尺寸
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include <QtWidgets/QGraphicsObject>

HE_BEGIN_NAMESPACE

class HGraphicsPixmapItemPrivate;

class HGraphicsPixmapItem : public QGraphicsObject
{
    Q_OBJECT

public:
    explicit HGraphicsPixmapItem(QGraphicsItem *parent = nullptr);
    ~HGraphicsPixmapItem() override;

public:
    enum { Type = UserType + 22 };
    int type() const override;

public:
    QString title() const;
    QPixmap pixmap() const;
    QColor textColor() const;

public:
    void setTitle(const QString &);
    void setPixmap(const QPixmap &);
    void setTextColor(const QColor &);

protected:
    HGraphicsPixmapItem(HGraphicsPixmapItemPrivate &p, QGraphicsItem *parent = nullptr);

protected:
    QRectF boundingRect() const override;
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *) override;
    void hoverMoveEvent(QGraphicsSceneHoverEvent *) override;

protected:
    QScopedPointer<HGraphicsPixmapItemPrivate> d_ptr;

private:
    void init();
    void openPixmap();
    bool isInResizeArea(const QPointF &);
};

HE_END_NAMESPACE

