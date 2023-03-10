#pragma once

#include "HAbstractDataItem.h"

HE_BEGIN_NAMESPACE

class HAbstractDataItemPrivate
{
public:
    QVariantMap datas;
    bool modified = true;
};

HE_END_NAMESPACE
