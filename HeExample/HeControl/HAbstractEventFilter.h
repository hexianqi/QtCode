/***************************************************************************************************
**      2019-09-03  HAbstractEventFilter
***************************************************************************************************/

#ifndef HABSTRACTEVENTFILTER_H
#define HABSTRACTEVENTFILTER_H

#include "IEventFilter.h"
#include <QtCore/QObject>

HE_CONTROL_BEGIN_NAMESPACE

class HAbstractEventFilterPrivate;

class HAbstractEventFilter : public QObject, public IEventFilter
{
    Q_OBJECT

public:
    explicit HAbstractEventFilter(QObject *parent = nullptr);
    ~HAbstractEventFilter() override;

public:
    bool setValidRegion(QRectF value) override;
    bool setEnable(bool b) override;
    bool isEnable() override;
    void setHandleFunc(QMap<QEvent::Type, std::function<bool(QEvent *)>> value) override;

public:
    bool eventFilter(QObject *, QEvent *) override;

protected:
    HAbstractEventFilter(HAbstractEventFilterPrivate &p, QObject *parent = nullptr);

protected:
    QScopedPointer<HAbstractEventFilterPrivate> d_ptr;
};

HE_CONTROL_END_NAMESPACE

#endif // HABSTRACTEVENTFILTER_H
