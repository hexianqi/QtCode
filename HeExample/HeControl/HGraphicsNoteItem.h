/***************************************************************************************************
**      2022-08-31  HGraphicsNoteItem
***************************************************************************************************/

#pragma once

#include "HGraphicsObject.h"

HE_BEGIN_NAMESPACE

class HGraphicsNoteItemPrivate;

class HGraphicsNoteItem : public HGraphicsObject
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HGraphicsNoteItem)

public:
    explicit HGraphicsNoteItem(QGraphicsItem *parent = nullptr);
    ~HGraphicsNoteItem() override;

public:
    enum { Type = UserType + 25 };
    int type() const override;

public:
    void setTitle(const QString &);
    void setContent(const QStringList &);

protected:
    HGraphicsNoteItem(HGraphicsNoteItemPrivate &p, QGraphicsItem *parent = nullptr);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *) override;
    void drawContent(QPainter *painter, const QStyleOptionGraphicsItem *option) override;
    void buttonPressed(int);
    void textPressed(int);
};

HE_END_NAMESPACE
