/***************************************************************************************************
**      2019-12-13  HResizeEventFilter
***************************************************************************************************/

#pragma once

#include "HAbstractMouseEventFilter.h"

HE_CONTROL_BEGIN_NAMESPACE

class HResizeEventFilterPrivate;

class HResizeEventFilter : public HAbstractMouseEventFilter
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HResizeEventFilter)

public:
    explicit HResizeEventFilter(QObject *parent = nullptr);

public:
    QString typeName() override;

public:
    bool addWatched(QObject *) override;

protected:
    HResizeEventFilter(HResizeEventFilterPrivate &p, QObject *parent = nullptr);

protected:
    bool handleEvent(QObject *, QEvent *) override;
    bool handleMousePressEvent(QWidget *, QMouseEvent *) override;
    bool handleMouseReleaseEvent(QWidget *, QMouseEvent *) override;
    bool handleMouseMoveEvent(QWidget *, QMouseEvent *) override;
    bool handleResizeEvent(QWidget *, QEvent *);
    bool handleHoverMoveEvent(QWidget *, QEvent *);
};

HE_CONTROL_END_NAMESPACE
