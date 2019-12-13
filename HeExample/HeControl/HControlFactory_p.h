#ifndef HCONTROLFACTORY_P_H
#define HCONTROLFACTORY_P_H

#include "HControlFactory.h"

HE_CONTROL_BEGIN_NAMESPACE

class HControlFactoryPrivate
{
public:
    QStringList supportedWidgets;
    QStringList supportedEventFilters;
};

HE_CONTROL_END_NAMESPACE

#endif // HCONTROLFACTORY_P_H
