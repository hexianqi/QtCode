#pragma once

#include "HControlFactoryWidget.h"

HE_CONTROL_BEGIN_NAMESPACE

class IControlFactory;

class HControlFactoryWidgetPrivate
{
public:
    IControlFactory *factory = nullptr;
};

HE_CONTROL_END_NAMESPACE
