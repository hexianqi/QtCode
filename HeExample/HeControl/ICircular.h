/***************************************************************************************************
**      2019-06-19  ICircular 等待策略。
***************************************************************************************************/

#pragma once

#include "HControlGlobal.h"
#include "HeCore/IInitializeable.h"

class QPainter;

HE_CORE_USE_NAMESPACE

HE_CONTROL_BEGIN_NAMESPACE

class ICircular : public QObject, public IInitializeable
{
    Q_OBJECT

public:
    using QObject::QObject;

signals:
    void dataChanged();

public:
    // 绘制
    virtual void draw(QPainter *, double factor, QVariantMap param = QVariantMap()) = 0;
};

HE_CONTROL_END_NAMESPACE
