/***************************************************************************************************
**      2019-06-06  HAbstractMouseEventFilter 抽象鼠标事件过滤器。
***************************************************************************************************/

#pragma once

#include "HAbstractEventFilter.h"

class QMouseEvent;

HE_CONTROL_BEGIN_NAMESPACE

class HAbstractMouseEventFilterPrivate;

class HAbstractMouseEventFilter : public HAbstractEventFilter
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HAbstractMouseEventFilter)

public:
    explicit HAbstractMouseEventFilter(QObject *parent = nullptr);

public:
    bool addWatched(QObject *) override;

protected:
    HAbstractMouseEventFilter(HAbstractMouseEventFilterPrivate &p, QObject *parent = nullptr);

protected:
    bool handleEvent(QObject *, QEvent *) override;
    virtual bool handleMousePressEvent(QWidget *, QMouseEvent *) = 0;
    virtual bool handleMouseReleaseEvent(QWidget *, QMouseEvent *) = 0;
    virtual bool handleMouseMoveEvent(QWidget *, QMouseEvent *) = 0;
};

HE_CONTROL_END_NAMESPACE
