/***************************************************************************************************
**      2019-06-13  IControlFactory 控件工厂接口。
***************************************************************************************************/

#ifndef ICONTROLFACTORY_H
#define ICONTROLFACTORY_H

#include "HControlGlobal.h"
#include "HeCore/IInitializeable.h"

HE_CORE_USE_NAMESPACE

HE_CONTROL_BEGIN_NAMESPACE

class IControlFactory : public IInitializeable
{
public:
    // 所有窗体
    virtual QStringList keys() = 0;
    // 创建窗体
    virtual QWidget *createWidget(QString type, QWidget *parent = nullptr) = 0;
};

HE_CONTROL_END_NAMESPACE

#endif // ICONTROLFACTORY_H
