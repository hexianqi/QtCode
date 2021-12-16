#include "HFactory.h"

HE_BEGIN_NAMESPACE

QHash<QString, std::function<void *()>> HFactory::__hashConstructor;

QStringList HFactory::keys()
{
    return __hashConstructor.keys();
}

HE_END_NAMESPACE
