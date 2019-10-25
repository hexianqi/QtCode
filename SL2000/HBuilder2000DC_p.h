#ifndef HBUILDER2000DC_P_H
#define HBUILDER2000DC_P_H

#include "HBuilder2000DC.h"
#include "HeGui/HAbstractBuilder_p.h"

class HBuilder2000DCPrivate : public HAbstractBuilderPrivate
{
public:
    using HAbstractBuilderPrivate::HAbstractBuilderPrivate;

public:
    QStringList sqlField;
};

#endif // HBUILDER2000DC_P_H
