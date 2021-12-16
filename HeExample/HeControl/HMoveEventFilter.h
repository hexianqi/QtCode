/***************************************************************************************************
**      2019-06-06  HMoveEventFilter 移动事件过滤器。
***************************************************************************************************/

#pragma once

#include "HAbstractMouseEventFilter.h"

HE_BEGIN_NAMESPACE

class HMoveEventFilterPrivate;

class HMoveEventFilter : public HAbstractMouseEventFilter
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HMoveEventFilter)

public:
    explicit HMoveEventFilter(QObject *parent = nullptr);

public:
    QString typeName() override;

protected:
    bool handleMousePressEvent(QWidget *, QMouseEvent *) override;
    bool handleMouseReleaseEvent(QWidget *, QMouseEvent *) override;
    bool handleMouseMoveEvent(QWidget *, QMouseEvent *) override;
};

HE_END_NAMESPACE
