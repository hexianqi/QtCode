/***************************************************************************************************
**      2022-08-26  HGraphicsPixmapItem 拖拽图形项改变尺寸
***************************************************************************************************/

#pragma once

#include "HGraphicsObject.h"

HE_BEGIN_NAMESPACE

class HGraphicsPixmapItemPrivate;

class HGraphicsPixmapItem : public HGraphicsObject
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HGraphicsPixmapItem)

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
    void init() override;
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *) override;
    void drawContent(QPainter *painter, const QStyleOptionGraphicsItem *option) override;

private:
    void openFile();
};

HE_END_NAMESPACE

