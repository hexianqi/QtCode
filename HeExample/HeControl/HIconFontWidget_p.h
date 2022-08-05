#pragma once

#include "HIconFontWidget.h"
#include <QtWidgets/QGraphicsTextItem>

class QGraphicsScene;

HE_BEGIN_NAMESPACE

class HIconFontFactory;

class HIconFontWidgetPrivate
{
public:
    QGraphicsScene *scene = nullptr;
    HIconFontFactory *fontFactory = nullptr;
    QFont font;
    QString fontFamily;
    int iconSize = 40;
};

class HGraphicsTextItem : public QGraphicsTextItem
{
public:
    explicit HGraphicsTextItem(QGraphicsItem *parent = nullptr);

protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent *) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *) override;
};

HE_END_NAMESPACE
