/***************************************************************************************************
**      2019-12-13  HResizeEventFilter
***************************************************************************************************/

#ifndef HRESIZEEVENTFILTER_H
#define HRESIZEEVENTFILTER_H

#include "HAbstractEventFilter.h"

class QMouseEvent;

HE_CONTROL_BEGIN_NAMESPACE

class HResizeEventFilterPrivate;

class HResizeEventFilter : public HAbstractEventFilter
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HResizeEventFilter)

public:
    explicit HResizeEventFilter(QObject *parent = nullptr);
    ~HResizeEventFilter() override;

public:
    void initialize(QVariantMap param) override;
    QString typeName() override;

public:
    bool addWatched(QObject *) override;

protected:
    HResizeEventFilter(HResizeEventFilterPrivate &p, QObject *parent = nullptr);

protected:
    bool handleInternal(QObject *, QEvent *) override;
    virtual bool resizeEvent(QWidget *, QEvent *);
    virtual bool mousePressEvent(QWidget *, QMouseEvent *) = 0;
    virtual bool mouseReleaseEvent(QWidget *, QMouseEvent *) = 0;
    virtual bool hoverMoveEvent(QWidget *, QMouseEvent *) = 0;
};

HE_CONTROL_END_NAMESPACE

#endif // HRESIZEEVENTFILTER_H
