/***************************************************************************************************
**      2018-06-19  HPositionTracking 鼠标位置追踪策略。
***************************************************************************************************/

#pragma once

#include "HAbstractMouseStrategy.h"
#include <QtCore/QPointF>

class HPositionTrackingPrivate;

class HPositionTracking : public HAbstractMouseStrategy
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HPositionTracking)

public:
    explicit HPositionTracking(QWidget *parent = nullptr);

signals:
    void positionChanged(QPointF pos);

public:
    virtual bool mousePressEvent(QMouseEvent *) override;
    virtual bool mouseMoveEvent(QMouseEvent *) override;
    virtual bool mouseReleaseEvent(QMouseEvent *) override;

protected:
    HPositionTracking(HPositionTrackingPrivate &p, QWidget *parent = nullptr);
};
