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
    explicit HAbstractMouseEventFilter(QWidget *parent = nullptr);
    ~HAbstractMouseEventFilter() override;

public:
    bool eventFilter(QObject *, QEvent *) override;

protected:
    HAbstractMouseEventFilter(HAbstractMouseEventFilterPrivate &p, QWidget *parent = nullptr);

protected:
    virtual bool isValid(QPointF pos);
    virtual bool mousePressEvent(QMouseEvent *) = 0;
    virtual bool mouseReleaseEvent(QMouseEvent *) = 0;
    virtual bool mouseMoveEvent(QMouseEvent *) = 0;
};

HE_CONTROL_END_NAMESPACE

#endif // HABSTRACTMOUSEEVENTFILTER_H
