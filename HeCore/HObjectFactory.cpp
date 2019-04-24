#include "HObjectFactory.h"

HE_CORE_BEGIN_NAMESPACE

QHash<QString, std::function<QObject *(QObject *)>> HObjectFactory::__hashConstructor;

HE_CORE_END_NAMESPACE
