/***************************************************************************************************
**      2018-06-19  ITestData 测试数据接口。
***************************************************************************************************/

#ifndef ITESTDATA_H
#define ITESTDATA_H

#include "HControllerGlobal.h"
#include "HeCore/IInitializeable.h"
#include <QVariant>

HE_CORE_USE_NAMESPACE

HE_CONTROLLER_BEGIN_NAMESPACE

class ITestData : public IInitializeable
{
public:
    // 设置后继者
    virtual void setSuccessor(ITestData *) = 0;
    // 设置数据
    virtual void setData(QString type, QVariant value) = 0;
    // 获取数据
    virtual QVariant data(QString type) = 0;
};

HE_CONTROLLER_END_NAMESPACE

#endif // ITESTDATA_H
