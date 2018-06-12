#ifndef HVERNIERTRACKING_P_H
#define HVERNIERTRACKING_P_H

#include "HVernierTracking.h"
#include "HAbstractMouseStrategy_p.h"
#include <QColor>
#include <QVector>

class HVernierTrackingPrivate : public HAbstractMouseStrategyPrivate
{
public:
    HVernierTrackingPrivate(Qt::Orientation o, QWidget *p);

public:
    void setValidRegion(QRectF value);
    void setVernier(int size);
    void setVernier(int i, double percent);

public:
    void paintVernier(QStylePainter *);
    bool mousePress(QPointF point);
    void mouseRelease();

public:
    Qt::Orientation orientation;
    QColor color = Qt::blue;
    int pos = -1;
    QVector<QPointF> verniers;
};

#endif // HVERNIERTRACKING_P_H
