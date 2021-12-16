/***************************************************************************************************
**      2019-12-17  HBackgroundEventFilter
***************************************************************************************************/

#pragma once

#include "HAbstractMouseEventFilter.h"

HE_BEGIN_NAMESPACE

class HBackgroundEventFilterPrivate;

class HBackgroundEventFilter : public HAbstractMouseEventFilter
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HBackgroundEventFilter)

public:
    explicit HBackgroundEventFilter(QObject *parent = nullptr);

public:
    void initialize(QVariantMap param = QVariantMap()) override;
    QString typeName() override;

public:
    bool addWatched(QObject *) override;

public:
    void setBackgroundImage(const QStringList &);
    void setBackgroundRepeated(bool b);
    void setBackgroundStretched(bool b);

protected:
    HBackgroundEventFilter(HBackgroundEventFilterPrivate &p, QObject *parent = nullptr);

protected:
    bool handleMousePressEvent(QWidget *, QMouseEvent *) override;
    bool handleMouseReleaseEvent(QWidget *, QMouseEvent *) override;
    bool handleMouseMoveEvent(QWidget *, QMouseEvent *) override;

protected:
    void updateBackground();
    void updateBackground(QWidget *);
};

HE_END_NAMESPACE
