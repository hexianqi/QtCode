/***************************************************************************************************
**      2019-06-06  HAbstractMouseEventFilter 抽象鼠标事件过滤器。
***************************************************************************************************/

#ifndef HABSTRACTMOUSEEVENTFILTER_H
#define HABSTRACTMOUSEEVENTFILTER_H

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
    ~HAbstractMouseEventFilter() override;

public:
    bool addWatched(QObject *) override;

protected:
    HAbstractMouseEventFilter(HAbstractMouseEventFilterPrivate &p, QObject *parent = nullptr);

protected:
    bool handleInternal(QObject *, QEvent *) override;
    virtual bool mousePressEvent(QWidget *, QMouseEvent *) = 0;
    virtual bool mouseReleaseEvent(QWidget *, QMouseEvent *) = 0;
    virtual bool mouseMoveEvent(QWidget *, QMouseEvent *) = 0;
};

HE_CONTROL_END_NAMESPACE

#endif // HABSTRACTMOUSEEVENTFILTER_H
