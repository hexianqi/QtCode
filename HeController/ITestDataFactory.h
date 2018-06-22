/***************************************************************************************************
**      2018-06-19  ITestDataFactory 测试数据工厂接口。
***************************************************************************************************/

#ifndef ITESTDATAFACTORY_H
#define ITESTDATAFACTORY_H

#include "HControllerGlobal.h"
#include "HeCore/IInitializeable.h"

HE_CORE_USE_NAMESPACE

HE_CONTROLLER_BEGIN_NAMESPACE

class ITestData;
class ITestSpec;

class ITestDataFactory : public IInitializeable
{
public:
    // 创建测试数据
    virtual ITestData *createTestData(QString type, QVariantMap param = QVariantMap()) = 0;
    // 创建光谱数据
    virtual ITestSpec *createTestSpec(QString type, QVariantMap param = QVariantMap()) = 0;
};

HE_CONTROLLER_END_NAMESPACE

#endif // ITESTDATAFACTORY_H
