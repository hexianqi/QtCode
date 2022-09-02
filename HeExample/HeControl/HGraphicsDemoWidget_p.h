#pragma once

#include "HGraphicsDemoWidget.h"

class QGraphicsScene;

HE_BEGIN_NAMESPACE

class HGraphicsObject;

class HGraphicsDemoWidgetPrivate
{
public:
    QGraphicsScene *scene;
    QList<HGraphicsObject *> items;

};

HE_END_NAMESPACE
