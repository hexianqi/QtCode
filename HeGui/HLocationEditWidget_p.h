#pragma once

#include "HLocationEditWidget.h"

HE_BEGIN_NAMESPACE

class IDataFactory;

class HLocationEditWidgetPrivate
{
public:
    HLocationEditWidgetPrivate();

public:
    IDataFactory *factory = nullptr;
    ILocation *data = nullptr;
};

HE_END_NAMESPACE
