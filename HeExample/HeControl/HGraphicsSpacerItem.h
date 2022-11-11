/***************************************************************************************************
**      2022-10-25  HGraphicsSpacerItem
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include <QtWidgets/QGraphicsObject>
#include <QtWidgets/QGraphicsLayoutItem>

HE_BEGIN_NAMESPACE

class HGraphicsSpacerItemPrivate;

class HGraphicsSpacerItem : public QGraphicsObject, public QGraphicsLayoutItem
{
    Q_OBJECT

public:
    explicit HGraphicsSpacerItem(int w, int h, QSizePolicy::Policy hPolicy = QSizePolicy::Maximum, QSizePolicy::Policy vPolicy = QSizePolicy::Maximum, QGraphicsItem *parent = nullptr);
    ~HGraphicsSpacerItem() override;

public:
    QSizeF sizeHint(Qt::SizeHint which, const QSizeF &constraint = QSizeF()) const override;
    QRectF boundingRect() const override;
    void setGeometry(const QRectF &) override;

protected:
    HGraphicsSpacerItem(HGraphicsSpacerItemPrivate &p, QGraphicsItem *parent = nullptr);

protected:
    virtual void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *) override;

protected:
    QScopedPointer<HGraphicsSpacerItemPrivate> d_ptr;
};

HE_END_NAMESPACE
