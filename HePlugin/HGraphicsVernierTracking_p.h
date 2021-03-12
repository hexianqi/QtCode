#pragma once

#include "HGraphicsVernierTracking.h"
#include "HAbstractVernierTracking_p.h"

class QGraphicsLineItem;

class HGraphicsVernierTrackingPrivate : public HAbstractVernierTrackingPrivate
{
public:
    HGraphicsVernierTrackingPrivate(Qt::Orientation o, QGraphicsItem *gp, QWidget *p);

public:
    QGraphicsItem *gparent;
    QList<QGraphicsLineItem *> lines;
};
