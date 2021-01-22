#pragma once

#include "HBuilder2100DC.h"
#include "HeGui/HAbstractBuilder_p.h"

class HBuilder2100DCPrivate : public HAbstractBuilderPrivate
{
public:
    HBuilder2100DCPrivate();

public:
    QStringList sqlField;

};
