#include "HWidgetFactory.h"

HE_BEGIN_NAMESPACE

QHash<QString, std::function<QWidget *(QWidget *)>> HWidgetFactory::__hashConstructor;

QStringList HWidgetFactory::keys()
{
    return __hashConstructor.keys();
}

HE_END_NAMESPACE
