#pragma once

#include "HGraphicsDemoWidget.h"

class QGraphicsScene;

HE_BEGIN_NAMESPACE

class HTestGraphicsItem;

class HGraphicsDemoWidgetPrivate
{
public:
    QGraphicsScene *scene;
    QList<HTestGraphicsItem *> items;

};

HE_END_NAMESPACE
