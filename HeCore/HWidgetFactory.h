/***************************************************************************************************
**      2019-05-14  HWidgetFactory QWidget类反射工厂类。
**                  调用方法：
**                  1.注册你的class（必须继承QWidget）：
**                      HWidgetFactory::registerClass<MyWidget>();
**                  2.反射构建一个新对象：
**                      MyWidget* object = HWidgetFactory::createWidget<MyWidget>("MyWidget");
***************************************************************************************************/

#ifndef HWIDGETFACTORY_H
#define HWIDGETFACTORY_H

#include "IInitializeable.h"
#include <QtCore/QVariant>
#include <functional>

HE_CORE_BEGIN_NAMESPACE

class HE_CORE_EXPORT HWidgetFactory
{
public:
    // 注册类
    template <typename T>
    static void registerClass(QString className = QString());
    // 创建对象
    template <typename T>
    static T *createWidget(QString className, QWidget *parent = nullptr);
    // 创建对象
    template <typename T>
    static T *createWidget(QString className, QVariantMap param, QWidget *parent = nullptr);

protected:
    template <typename T>
    static QWidget *constructorHelper(QWidget *parent);

protected:
    static QHash<QString, std::function<QWidget *(QWidget *)>> __hashConstructor;
};

template <typename T>
void HWidgetFactory::registerClass(QString className)
{
    if (className.isEmpty())
        className = T::staticMetaObject.className();
    __hashConstructor.insert(className, &constructorHelper<T>);
}

template <typename T>
T *HWidgetFactory::createWidget(QString className, QWidget *parent)
{
    if (!__hashConstructor.contains(className))
        return nullptr;
    return qobject_cast<T *>(__hashConstructor[className](parent));
}

template <typename T>
T *HWidgetFactory::createWidget(QString className, QVariantMap param, QWidget *parent)
{
    static_assert(std::is_base_of<IInitializeable, T>::value, "T needs to be IInitializeable based.");
    auto t = createWidget<T>(className, parent);
    if (t != nullptr)
        t->initialize(param);
    return t;
}

template <typename T>
QWidget *HWidgetFactory::constructorHelper(QWidget *parent)
{
    return new T(parent);
}

HE_CORE_END_NAMESPACE

#endif // HWIDGETFACTORY_H
