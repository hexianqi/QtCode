#pragma once

#include "HChromatismEditWidget.h"

HE_BEGIN_NAMESPACE

class IDataFactory;

class HChromatismEditWidgetPrivate
{
public:
    HChromatismEditWidgetPrivate();

public:
    IDataFactory *factory = nullptr;
    IChromatism *data = nullptr;
};

HE_END_NAMESPACE
