/***************************************************************************************************
**      2018-07-03  HGraphicsVernierTracking Graphics游标追踪策略。
***************************************************************************************************/

#ifndef HGRAPHICSVERNIERTRACKING_H
#define HGRAPHICSVERNIERTRACKING_H

#include "HAbstractVernierTracking.h"

class QGraphicsItem;
class HGraphicsVernierTrackingPrivate;

class HGraphicsVernierTracking : public HAbstractVernierTracking
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HGraphicsVernierTracking)

public:
    explicit HGraphicsVernierTracking(Qt::Orientation orientation, QGraphicsItem *gpatent = nullptr, QWidget *parent = nullptr);
    ~HGraphicsVernierTracking();

public:
    virtual bool setEnable(bool b) override;

public:
    virtual bool mouseMoveEvent(QMouseEvent *) override;

protected:
    HGraphicsVernierTracking(HGraphicsVernierTrackingPrivate &p, QWidget *parent = nullptr);
};

#endif // HGRAPHICSVERNIERTRACKING_H
