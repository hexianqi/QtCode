/***************************************************************************************************
**      2019-06-19  IWait 等待策略。
***************************************************************************************************/

#ifndef IWAIT_H
#define IWAIT_H

#include "HControlGlobal.h"
#include "HeCore/IInitializeable.h"

class QPainter;

HE_CORE_USE_NAMESPACE

HE_CONTROL_BEGIN_NAMESPACE

class IWait : public QObject, public IInitializeable
{
    Q_OBJECT

public:
    using QObject::QObject;

signals:
    void dataChanged();

public:
    // 绘制
    virtual void draw(QPainter *, QVariantMap param = QVariantMap()) = 0;
};

HE_CONTROL_END_NAMESPACE

#endif // IWAIT_H
