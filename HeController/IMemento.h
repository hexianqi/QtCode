/***************************************************************************************************
**      2019-05-27  IMemento 备忘录接口。
***************************************************************************************************/

#ifndef IMEMENTO_H
#define IMEMENTO_H

#include "HControllerGlobal.h"
#include "HeCore/IInitializeable.h"

HE_CORE_USE_NAMESPACE

HE_CONTROLLER_BEGIN_NAMESPACE

class HE_CONTROLLER_EXPORT IMemento : public QObject, public IInitializeable
{
    Q_OBJECT

public:
    using QObject::QObject;

public:
    // 保存
    virtual void save() = 0;
    // 还原
    virtual void restore() = 0;
};

HE_CONTROLLER_END_NAMESPACE

#endif // IMEMENTO_H
