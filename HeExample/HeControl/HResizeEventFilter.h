/***************************************************************************************************
**      2019-12-13  HResizeEventFilter
***************************************************************************************************/

#ifndef HRESIZEEVENTFILTER_H
#define HRESIZEEVENTFILTER_H

#include "HAbstractMouseEventFilter.h"

HE_CONTROL_BEGIN_NAMESPACE

class HResizeEventFilterPrivate;

class HResizeEventFilter : public HAbstractMouseEventFilter
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
    bool mousePressEvent(QWidget *, QMouseEvent *) override;
    bool mouseReleaseEvent(QWidget *, QMouseEvent *) override;
    bool mouseMoveEvent(QWidget *, QMouseEvent *) override;
    bool resizeEvent(QWidget *, QEvent *);
    bool hoverMoveEvent(QWidget *, QEvent *);
};

HE_CONTROL_END_NAMESPACE

#endif // HRESIZEEVENTFILTER_H
