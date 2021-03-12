#pragma once

#include "HBuilder2000.h"
#include "HeGui/HAbstractBuilder_p.h"

class HBuilder2000Private : public HAbstractBuilderPrivate
{
public:
    HBuilder2000Private();

public:
    QStringList sqlField;
};
