#pragma once

#include "HControlFactoryWidget.h"

HE_BEGIN_NAMESPACE

class IControlFactory;

class HControlFactoryWidgetPrivate
{
public:
    IControlFactory *factory = nullptr;
};

HE_END_NAMESPACE
