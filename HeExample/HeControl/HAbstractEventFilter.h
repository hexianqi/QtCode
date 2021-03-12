/***************************************************************************************************
**      2019-09-03  HAbstractEventFilter
***************************************************************************************************/

#pragma once

#include "IEventFilter.h"

HE_CONTROL_BEGIN_NAMESPACE

class HAbstractEventFilterPrivate;

class HAbstractEventFilter : public IEventFilter
{
    Q_OBJECT

public:
    explicit HAbstractEventFilter(QObject *parent = nullptr);
    ~HAbstractEventFilter() override;

public:
    bool setEnable(bool b) override;
    bool isEnable() override;
    bool addWatched(QObject *) override;
    void addHandler(QEvent::Type type, std::function<bool(QEvent *)> func) override;

public:
    bool eventFilter(QObject *, QEvent *) override;

protected:
    HAbstractEventFilter(HAbstractEventFilterPrivate &p, QObject *parent = nullptr);

protected:
    virtual bool hasWatched(QObject *);
    virtual bool hasHandler(QEvent::Type t);
    virtual bool handleEvent(QObject *, QEvent *) = 0;

protected:
    QScopedPointer<HAbstractEventFilterPrivate> d_ptr;
};

HE_CONTROL_END_NAMESPACE
