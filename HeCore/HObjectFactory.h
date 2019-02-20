/***************************************************************************************************
**      2018-06-19  HObjectFactory QObject类反射工厂类。
***************************************************************************************************/

#ifndef HOBJECTFACTORY_H
#define HOBJECTFACTORY_H

#include "IInitializeable.h"
#include <functional>
#include <QVariant>

HE_CORE_BEGIN_NAMESPACE

class HE_CORE_EXPORT HObjectFactory
{
public:
    // 注册类
    template<typename T>
    static void registerClass(QString className = QString());
    // 创建对象
    template<typename T>
    static T *createObject(QString className, QObject *parent = nullptr);
    // 创建对象
    template<typename T>
    static T *createObject(QString className, QVariantMap param, QObject *parent = nullptr);

protected:
    template<typename T>
    static QObject *constructorHelper(QObject *parent);

protected:
    static QHash<QString, std::function<QObject *(QObject *)>> __hashConstructor;
};

template<typename T>
void HObjectFactory::registerClass(QString className)
{
    if (className.isEmpty())
        className = T::staticMetaObject.className();
    __hashConstructor.insert(className, &constructorHelper<T>);
}

template<typename T>
T *HObjectFactory::createObject(QString className, QObject *parent)
{
    if (!__hashConstructor.contains(className))
        return nullptr;
    return qobject_cast<T *>(__hashConstructor[className](parent));
}

template<typename T>
T *HObjectFactory::createObject(QString className, QVariantMap param, QObject *parent)
{
    static_assert(std::is_base_of<IInitializeable, T>::value, "T needs to be IInitializeable based.");
    auto t = createObject<T>(className, parent);
    if (t != nullptr)
        t->initialize(param);
    return t;
}

template<typename T>
QObject *HObjectFactory::constructorHelper(QObject *parent)
{
    return new T(parent);
}

HE_CORE_END_NAMESPACE

#endif // HOBJECTFACTORY_H
