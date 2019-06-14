#include "HFactory.h"

HE_CORE_BEGIN_NAMESPACE

QHash<QString, std::function<void *()>> HFactory::__hashConstructor;

QStringList HFactory::keys()
{
    return __hashConstructor.keys();
}

HE_CORE_END_NAMESPACE
