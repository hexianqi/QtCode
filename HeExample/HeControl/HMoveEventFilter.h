/***************************************************************************************************
**      2019-06-06  HMoveEventFilter 移动事件过滤器。
***************************************************************************************************/

#ifndef HMOVEEVENTFILTER_H
#define HMOVEEVENTFILTER_H

#include "HAbstractMouseEventFilter.h"

HE_CONTROL_BEGIN_NAMESPACE

class HMoveEventFilterPrivate;

class HMoveEventFilter : public HAbstractMouseEventFilter
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HMoveEventFilter)

public:
    explicit HMoveEventFilter(QObject *parent = nullptr);

public:
    void initialize(QVariantMap param) override;
    QString typeName() override;

protected:
    bool handleMousePressEvent(QWidget *, QMouseEvent *) override;
    bool handleMouseReleaseEvent(QWidget *, QMouseEvent *) override;
    bool handleMouseMoveEvent(QWidget *, QMouseEvent *) override;
};

HE_CONTROL_END_NAMESPACE

#endif // HMOVEEVENTFILTER_H
