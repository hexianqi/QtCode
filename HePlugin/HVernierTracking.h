/***************************************************************************************************
**      2018-06-19  HVernierTracking 游标追踪策略。
***************************************************************************************************/

#pragma once

#include "HAbstractVernierTracking.h"

class QPaintEvent;
class HVernierTrackingPrivate;

class QDESIGNER_WIDGET_EXPORT HVernierTracking : public HAbstractVernierTracking
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HVernierTracking)

public:
    explicit HVernierTracking(Qt::Orientation orientation, QWidget *parent = nullptr);

public:
    virtual void paintEvent(QPaintEvent *);
    virtual bool mouseMoveEvent(QMouseEvent *) override;

protected:
    HVernierTracking(HVernierTrackingPrivate &p, QWidget *parent = nullptr);
};
