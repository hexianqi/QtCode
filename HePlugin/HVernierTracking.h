/***************************************************************************************************
**      2018-06-19  HVernierTracking 游标追踪策略。
***************************************************************************************************/

#ifndef HVERNIERTRACKING_H
#define HVERNIERTRACKING_H

#include "HAbstractVernierTracking.h"

class HVernierTrackingPrivate;

class HVernierTracking : public HAbstractVernierTracking
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HVernierTracking)

public:
    explicit HVernierTracking(Qt::Orientation orientation, QWidget *parent = nullptr);
    ~HVernierTracking();

public:
    virtual void paintEvent(QPaintEvent *);
    virtual bool mouseMoveEvent(QMouseEvent *) override;

protected:
    HVernierTracking(HVernierTrackingPrivate &p, QWidget *parent = nullptr);
};

#endif // HVERNIERTRACKING_H
