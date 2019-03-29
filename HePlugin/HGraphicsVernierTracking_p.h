#ifndef HGRAPHICSVERNIERTRACKING_P_H
#define HGRAPHICSVERNIERTRACKING_P_H

#include "HGraphicsVernierTracking.h"
#include "HAbstractVernierTracking_p.h"

class QGraphicsLineItem;

class HGraphicsVernierTrackingPrivate : public HAbstractVernierTrackingPrivate
{
public:
    HGraphicsVernierTrackingPrivate(Qt::Orientation o, QGraphicsItem *gp, QWidget *p);

public:
    QGraphicsItem *gparent;
    QVector<QGraphicsLineItem *> lines;
};

#endif // HGRAPHICSVERNIERTRACKING_P_H
