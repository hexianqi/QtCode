/***************************************************************************************************
**      2019-06-06  HAbstractMouseEventFilter 抽象鼠标事件过滤器。
***************************************************************************************************/

#ifndef HABSTRACTMOUSEEVENTFILTER_H
#define HABSTRACTMOUSEEVENTFILTER_H

#include "IEventFilter.h"
#include <QtCore/QObject>

class QMouseEvent;

HE_CONTROL_BEGIN_NAMESPACE

class HAbstractMouseEventFilterPrivate;

class HAbstractMouseEventFilter : public QObject, public IEventFilter
{
    Q_OBJECT

public:
    explicit HAbstractMouseEventFilter(QWidget *parent = nullptr);
    ~HAbstractMouseEventFilter() override;

public:
    bool setValidRegion(QRectF value) override;
    bool setEnable(bool b) override;
    bool isEnable() override;

public:
    bool eventFilter(QObject *, QEvent *) override;

protected:
    HAbstractMouseEventFilter(HAbstractMouseEventFilterPrivate &p, QWidget *parent = nullptr);

protected:
    virtual bool isValid(QPointF pos);
    virtual bool mousePressEvent(QMouseEvent *) = 0;
    virtual bool mouseReleaseEvent(QMouseEvent *) = 0;
    virtual bool mouseMoveEvent(QMouseEvent *) = 0;

protected:
    QScopedPointer<HAbstractMouseEventFilterPrivate> d_ptr;
};

HE_CONTROL_END_NAMESPACE

#endif // HABSTRACTMOUSEEVENTFILTER_H
