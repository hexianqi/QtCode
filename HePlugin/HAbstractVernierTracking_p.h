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
    virtual bool setValidRegion(QRectF value);
    virtual bool setOrientation(Qt::Orientation value);
    virtual bool setVernierColor(QColor value);
    virtual bool setVernier(int i, double percent);
    virtual void resizeVernier(int size);

public:
    bool mousePress(QPointF point);
    void mouseRelease();

public:
    Qt::Orientation orientation;
    QColor color = Qt::blue;
    int pos = -1;
    QVector<QPointF> verniers;
};

#endif // HABSTRACTVERNIERTRACKING_P_H
