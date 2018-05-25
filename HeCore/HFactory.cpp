#include "HFactory.h"

HE_CORE_BEGIN_NAMESPACE

QHash<QString, std::function<void *()>> HFactory::__hashConstructor;

HE_CORE_END_NAMESPACE
