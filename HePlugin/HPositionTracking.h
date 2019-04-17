/***************************************************************************************************
**      2018-06-19  HPositionTracking 鼠标位置追踪策略。
***************************************************************************************************/

#ifndef HPOSITIONTRACKING_H
#define HPOSITIONTRACKING_H

#include "HAbstractMouseStrategy.h"
#include <QtCore/QPointF>

class HPositionTrackingPrivate;

class HPositionTracking : public HAbstractMouseStrategy
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HPositionTracking)

public:
    explicit HPositionTracking(QWidget *parent = nullptr);
    ~HPositionTracking() override;

signals:
    void positionChanged(QPointF pos);

public:
    virtual bool mousePressEvent(QMouseEvent *) override;
    virtual bool mouseMoveEvent(QMouseEvent *) override;
    virtual bool mouseReleaseEvent(QMouseEvent *) override;

protected:
    HPositionTracking(HPositionTrackingPrivate &p, QWidget *parent = nullptr);
};

#endif // HPOSITIONTRACKING_H
