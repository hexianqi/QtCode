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
    virtual bool setOrientation(Qt::Orientation value) override;
    virtual bool setValidRegion(QRectF value) override;
    virtual bool setVernierColor(QColor value) override;
    virtual bool setVernier(int i, double percent) override;
    virtual void resizeVernier(int size) override;

public:
    void setLinesVisible(bool b);
    void setLinesColor(QColor color);
    void setLine(int pos);
    void setLines();

public:
    QGraphicsItem *gparent;
    QVector<QGraphicsLineItem *> lines;
};

#endif // HGRAPHICSVERNIERTRACKING_P_H
