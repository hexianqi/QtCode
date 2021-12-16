#pragma once

#include "HControlFactory.h"

HE_BEGIN_NAMESPACE

class HControlFactoryPrivate
{
public:
    QStringList supportedWidgets;
    QStringList supportedEventFilters;
};

HE_END_NAMESPACE
