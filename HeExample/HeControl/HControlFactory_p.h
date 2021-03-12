#pragma once

#include "HControlFactory.h"

HE_CONTROL_BEGIN_NAMESPACE

class HControlFactoryPrivate
{
public:
    QStringList supportedWidgets;
    QStringList supportedEventFilters;
};

HE_CONTROL_END_NAMESPACE
