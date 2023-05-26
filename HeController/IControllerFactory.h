/***************************************************************************************************
**      2018-06-19  IControllerFactory 控制器工厂接口。
***************************************************************************************************/

#pragma once

#include "HeCore/IInitializeable.h"

HE_BEGIN_NAMESPACE

class IThread;
class IThreadCollection;
class IModel;
class IActionStrategy;
class IMemento;
class IMementoCollection;

class IControllerFactory : public IInitializeable
{
public:
    // 创建线程
    virtual IThread *createThread(QString type, QObject *parent = nullptr, QVariantMap param = QVariantMap()) = 0;
    virtual IThreadCollection *createThreadCollection(QString type, QVariantMap param = QVariantMap()) = 0;
    // 创建模型
    virtual IModel *createModel(QString type, QObject *parent = nullptr, QVariantMap param = QVariantMap()) = 0;
    // 创建动作处理策略
    virtual IActionStrategy *createStrategy(QString type, QObject *parent = nullptr, QVariantMap param = QVariantMap()) = 0;
    // 创建备忘录
    virtual IMemento *createMemento(QString type, QObject *parent = nullptr, QVariantMap param = QVariantMap()) = 0;
    virtual IMementoCollection *createMementoCollection(QString type, QVariantMap param = QVariantMap()) = 0;
};

HE_END_NAMESPACE
