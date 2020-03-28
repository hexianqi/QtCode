#ifndef HSPECLUMINOUS_P_H
#define HSPECLUMINOUS_P_H

#include "HSpecLuminous.h"
#include "HAbstractDataItem_p.h"

HE_DATA_BEGIN_NAMESPACE

class HSpecLuminousPrivate : public HAbstractDataItemPrivate
{
public:
    QMap<QString, double> selfAbsorption;
};

HE_DATA_END_NAMESPACE

#endif // HSPECLUMINOUS_P_H
