#pragma once

#include "HControlFactory.h"

HE_BEGIN_NAMESPACE

class HControlFactoryPrivate
{
public:
    QStringList supportedWidget;
    QStringList supportedEventFilter;
};

HE_END_NAMESPACE
