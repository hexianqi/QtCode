/***************************************************************************************************
**      2019-05-14  HWidgetFactory QWidget类反射工厂类。
**                  调用方法：
**                  1.注册你的class（必须继承QWidget）：
**                      HWidgetFactory::registerClass<MyWidget>();
**                  2.反射构建一个新对象：
**                      MyWidget* object = HWidgetFactory::createWidget<MyWidget>("MyWidget");
***************************************************************************************************/

#pragma once

#include "IInitializeable.h"
#include <functional>

HE_BEGIN_NAMESPACE

class HWidgetFactory
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
    // 所有窗体名称
    static QStringList keys();

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
    auto p = createWidget<T>(className, parent);
    if (p != nullptr)
        p->initialize(param);
    return p;
}

template <typename T>
QWidget *HWidgetFactory::constructorHelper(QWidget *parent)
{
    return new T(parent);
}

HE_END_NAMESPACE
