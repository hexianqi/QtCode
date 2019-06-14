#include "HObjectFactory.h"

HE_CORE_BEGIN_NAMESPACE

QHash<QString, std::function<QObject *(QObject *)>> HObjectFactory::__hashConstructor;

QStringList HObjectFactory::keys()
{
    return __hashConstructor.keys();
}

HE_CORE_END_NAMESPACE
