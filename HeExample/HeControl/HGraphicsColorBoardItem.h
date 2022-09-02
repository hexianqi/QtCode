/***************************************************************************************************
**      2022-08-30  HGraphicsColorPieItem
***************************************************************************************************/

#pragma once

#include "HGraphicsObject.h"

HE_BEGIN_NAMESPACE

class HGraphicsColorBoardItemPrivate;

class HGraphicsColorBoardItem : public HGraphicsObject
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HGraphicsColorBoardItem)

public:
    explicit HGraphicsColorBoardItem(QGraphicsItem *parent = nullptr);
    ~HGraphicsColorBoardItem() override;

signals:
    void colorPicked(const QColor &);

public:
    enum { Type = UserType + 24 };
    int type() const override;

protected:
    HGraphicsColorBoardItem(HGraphicsColorBoardItemPrivate &p, QGraphicsItem *parent = nullptr);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *) override;
    void init() override;
    void drawContent(QPainter *painter, const QStyleOptionGraphicsItem *option) override;
    void buildGradient(int value);
    void buildPixmap();
    void colorPick(const QPointF &);
    bool isInBoard(const QPointF &);
    double radius(const QPointF &);
    double hue(const QPointF &);
    QPointF toRelative(const QPointF &);
    QPointF toAbsolute(const QPointF &);
};

HE_END_NAMESPACE
