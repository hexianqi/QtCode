#pragma once

#include "HSpecLuminous.h"
#include "HAbstractDataItem_p.h"

HE_BEGIN_NAMESPACE

class HSpecLuminousPrivate : public HAbstractDataItemPrivate
{
public:
    QMap<QString, double> selfAbsorption;
};

HE_END_NAMESPACE
