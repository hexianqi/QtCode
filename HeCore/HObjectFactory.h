#ifndef HOBJECTFACTORY_H
#define HOBJECTFACTORY_H

#include "HCoreGlobal.h"
#include <functional>
#include <QHash>
#include <QObject>

HE_CORE_BEGIN_NAMESPACE

class HE_CORE_EXPORT HObjectFactory
{
public:
    template<typename T>
    static void registerClass();

    template<typename T>
    static T *createObject(const QByteArray &className, QObject *parent = nullptr);

protected:
      template<typename T>
      static QObject *constructorHelper(QObject* parent);

protected:
    static QHash<QByteArray, std::function<QObject*(QObject*)>> __hashConstructor;
};

template<typename T>
T *HObjectFactory::createObject(const QByteArray &className, QObject *parent)
{
    if (!__hashConstructor.contains(className))
        return nullptr;
    return qobject_cast<T*>(__hashConstructor[className](parent));
}

HE_CORE_END_NAMESPACE

#endif // HOBJECTFACTORY_H
