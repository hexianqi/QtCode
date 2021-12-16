/***************************************************************************************************
**      2018-06-19  HFactory 类反射工厂类。
***************************************************************************************************/

#pragma once

#include "IInitializeable.h"
#include <functional>

HE_BEGIN_NAMESPACE

class HFactory
{
public:
    // 注册类
    template <typename T>
    static void registerClass(QString className);
    // 创建对象
    template <typename T>
    static T *createObject(QString className);
    // 创建对象
    template <typename T>
    static T *createObject(QString className, QVariantMap param);
    // 所有对象名称
    static QStringList keys();

protected:
    template <typename T>
    static void *constructorHelper();

protected:
    static QHash<QString, std::function<void *()>> __hashConstructor;
};

template <typename T>
void HFactory::registerClass(QString className)
{
    __hashConstructor.insert(className, &constructorHelper<T>);
}

template <typename T>
T *HFactory::createObject(QString className)
{
    if (!__hashConstructor.contains(className))
        return nullptr;
    return static_cast<T *>(__hashConstructor[className]());
}

template <typename T>
T *HFactory::createObject(QString className, QVariantMap param)
{
    static_assert(std::is_base_of<IInitializeable, T>::value, "T needs to be IInitializeable based.");
    auto p = createObject<T>(className);
    if (p != nullptr)
        p->initialize(param);
    return p;
}

template <typename T>
void *HFactory::constructorHelper()
{
    return new T();
}

HE_END_NAMESPACE
