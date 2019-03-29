#ifndef HABSTRACTVERNIERTRACKING_P_H
#define HABSTRACTVERNIERTRACKING_P_H

#include "HAbstractVernierTracking.h"
#include "HAbstractMouseStrategy_p.h"
#include <QColor>
#include <QVector>

class HAbstractVernierTrackingPrivate : public HAbstractMouseStrategyPrivate
{
public:
    HAbstractVernierTrackingPrivate(Qt::Orientation o, QWidget *p);

public:
    Qt::Orientation orientation;
    QColor color = Qt::blue;
    int pos = -1;
    QVector<QPointF> verniers;
};

#endif // HABSTRACTVERNIERTRACKING_P_H
