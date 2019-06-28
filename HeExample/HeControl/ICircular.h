/***************************************************************************************************
**      2019-06-19  ICircular 等待策略。
***************************************************************************************************/

#ifndef ICIRCULAR_H
#define ICIRCULAR_H

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
    virtual void draw(QPainter *, QVariantMap param = QVariantMap()) = 0;
};

HE_CONTROL_END_NAMESPACE

#endif // ICIRCULAR_H
