#ifndef HOBJECTFACTORY_H
#define HOBJECTFACTORY_H

#include "HCoreGlobal.h"
#include <functional>
#include <QHash>
#include <QObject>

HE_CORE_BEGIN_NAMESPACE

class HObjectFactory
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
    static QHash<QByteArray, std::function<QObject*(QObject*)>> hashConstructor;
};

HE_CORE_END_NAMESPACE

#endif // HOBJECTFACTORY_H
