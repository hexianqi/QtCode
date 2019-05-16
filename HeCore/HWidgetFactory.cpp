#include "HWidgetFactory.h"

HE_CORE_BEGIN_NAMESPACE

QHash<QString, std::function<QWidget *(QWidget *)>> HWidgetFactory::__hashConstructor;

HE_CORE_END_NAMESPACE
