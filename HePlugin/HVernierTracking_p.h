#ifndef HVERNIERTRACKING_P_H
#define HVERNIERTRACKING_P_H

#include "HVernierTracking.h"

class QStylePainter;

class HVernierTrackingPrivate
{
public:
    HVernierTrackingPrivate();

public:
    void setValidRegion(QRectF value);
    void setVernier(int size);
    void setVernier(int i, double percent);

public:
    void paintVernier(QStylePainter *);

public:
    Qt::Orientation orientation;
    bool enableTracking;
    QColor color;
    QRectF validRegion;
    QList<QPointF> verniers;
    int pos;
};

#endif // HVERNIERTRACKING_P_H
