/***************************************************************************************************
**      2018-06-19  IControllerFactory 控制器工厂接口。
***************************************************************************************************/

#ifndef ICONTROLLERFACTORY_H
#define ICONTROLLERFACTORY_H

#include "HControllerGlobal.h"
#include "HeCore/IInitializeable.h"

HE_CORE_USE_NAMESPACE

HE_CONTROLLER_BEGIN_NAMESPACE

class IThread;
class IThreadCollection;
class ITestData;
class ITestSpec;
class IModel;

class IControllerFactory : public IInitializeable
{
public:
    // 创建线程
    virtual IThread *createThread(QString type, QVariantMap param = QVariantMap()) = 0;
    // 创建线程集合
    virtual IThreadCollection *createThreadCollection(QString type, QVariantMap param = QVariantMap()) = 0;
    // 创建测试数据
    virtual ITestData *createTestData(QString type, QVariantMap param = QVariantMap()) = 0;
    // 创建光谱数据
    virtual ITestSpec *createTestSpec(QString type, QVariantMap param = QVariantMap()) = 0;
    // 创建模型
    virtual IModel *createModel(QString type, QVariantMap param = QVariantMap()) = 0;
};

HE_CONTROLLER_END_NAMESPACE

#endif // ICONTROLLERFACTORY_H
