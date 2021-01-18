#ifndef HBUILDER2000DC_P_H
#define HBUILDER2000DC_P_H

#include "HBuilder2000DC.h"
#include "HeGui/HAbstractBuilder_p.h"

class HBuilder2000DCPrivate : public HAbstractBuilderPrivate
{
public:
    HBuilder2000DCPrivate();

public:
    QStringList sqlField;
};

#endif // HBUILDER2000DC_P_H
