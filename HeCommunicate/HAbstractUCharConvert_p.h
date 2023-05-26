#pragma once

#include "HAbstractUCharConvert.h"

HE_BEGIN_NAMESPACE

class HAbstractUCharConvertPrivate
{
public:
    QHash<QVariant::Type, int> hashDigits;
};

HE_END_NAMESPACE

