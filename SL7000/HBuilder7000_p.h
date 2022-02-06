#pragma once

#include "HBuilder7000.h"
#include "HeGui/HAbstractBuilder_p.h"

class HBuilder7000Private : public HAbstractBuilderPrivate
{
public:
    HBuilder7000Private();

public:
    QStringList sqlField;
};
