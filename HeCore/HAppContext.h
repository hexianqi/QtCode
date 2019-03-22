/**********************************************************************************************************************
**  2018-06-19  HAppContext 上下文类。
**              获取上下文指针是需要注意事项：
**              1.单继承时：T类型必须是设置类型或其父类型。
**              2.多继承时：T类型必须是设置时的类型，不能是其父类。
**              例如：  HCommunicateFactory是QObject和ICommunicateFactory的子类。
**              setContextPointer("ICommunicateFactory", new HCommunicateFactory(this)); // 编译不会有问题，使用factory会出问题。
**              auto factory = HAppContext::getContextPointer<ICommunicateFactory>("ICommunicateFactory");
**              替换成：setContextPointer("ICommunicateFactory", new HCommunicateFactory(this));
**                      auto factory = HAppContext::getContextPointer<HCommunicateFactory>("ICommunicateFactory"); // ICommunicateFactory->HCommunicateFactory
**              替换成：ICommunicateFactory *factory = new HCommunicateFactory(this);
**                      setContextPointer("ICommunicateFactory", factory);
**                      auto factory = HAppContext::getContextPointer<ICommunicateFactory>("ICommunicateFactory");
**********************************************************************************************************************/

#ifndef HAPPCONTEXT_H
#define HAPPCONTEXT_H

#include "HCoreGlobal.h"
#include <QVariant>

HE_CORE_BEGIN_NAMESPACE

class HE_CORE_EXPORT HAppContext
{
public:
    // 设置上下文数值
    static void setContextValue(QString key, QVariant value);
    // 获取上下文数值
    static QVariant getContextValue(QString key);
    // 获取上下文数值
    template<typename T>
    static T getContextValue(QString key);
    // 设置上下文指针
    static void setContextPointer(QString key, void *value);
    // 获取上下文指针
    static void *getContextPointer(QString key);
    // 获取上下文指针
    template<typename T>
    static T *getContextPointer(QString key);

protected:
    static QHash<QString, QVariant> __contextValue;
    static QHash<QString, void *> __contextPointer;
};

template<typename T>
T HAppContext::getContextValue(QString key)
{
    return getContextValue(key).value<T>();
}

template<typename T>
T *HAppContext::getContextPointer(QString key)
{
    return static_cast<T *>(getContextPointer(key));
}

HE_CORE_END_NAMESPACE

#endif // HAPPCONTEXT_H
