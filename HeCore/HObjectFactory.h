/***************************************************************************************************
**      2018-06-19  HObjectFactory QObject类反射工厂类。
**                  调用方法：
**                  1.注册你的class（必须继承QObject）：
**                      HObjectFactory::registerClass<MyObject>();
**                  2.反射构建一个新对象：
**                      MyObject* object = HObjectFactory::createObject<MyObject>("MyObject");
***************************************************************************************************/

#pragma once

#include "IInitializeable.h"
#include <QtCore/QVariant>
#include <functional>

HE_CORE_BEGIN_NAMESPACE

class HE_CORE_EXPORT HObjectFactory
{
public:
    // 注册类
    template <typename T>
    static void registerClass(QString className = QString());
    // 创建对象
    template <typename T>
    static T *createObject(QString className, QObject *parent = nullptr);
    // 创建对象
    template <typename T>
    static T *createObject(QString className, QVariantMap param, QObject *parent = nullptr);
    // 所有对象名称
    static QStringList keys();

protected:
    template <typename T>
    static QObject *constructorHelper(QObject *parent);

protected:
    static QHash<QString, std::function<QObject *(QObject *)>> __hashConstructor;
};

template <typename T>
void HObjectFactory::registerClass(QString className)
{
    if (className.isEmpty())
        className = T::staticMetaObject.className();
    __hashConstructor.insert(className, &constructorHelper<T>);
}

template <typename T>
T *HObjectFactory::createObject(QString className, QObject *parent)
{
    if (!__hashConstructor.contains(className))
        return nullptr;
    return dynamic_cast<T *>(__hashConstructor[className](parent));
}

template <typename T>
T *HObjectFactory::createObject(QString className, QVariantMap param, QObject *parent)
{
    static_assert(std::is_base_of<IInitializeable, T>::value, "T needs to be IInitializeable based.");
    auto p = createObject<T>(className, parent);
    if (p != nullptr)
        p->initialize(param);
    return p;
}

template <typename T>
QObject *HObjectFactory::constructorHelper(QObject *parent)
{
    return new T(parent);
}

HE_CORE_END_NAMESPACE
