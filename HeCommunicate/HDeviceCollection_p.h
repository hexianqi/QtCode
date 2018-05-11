#ifndef HDEVICECOLLECTION_P_H
#define HDEVICECOLLECTION_P_H

#include "HDeviceCollection.h"

HE_COMMUNICATE_BEGIN_NAMESPACE

class HDeviceCollectionPrivate
{
public:
    QList<HActionType> additionals;
};

HE_COMMUNICATE_END_NAMESPACE

#endif // HDEVICECOLLECTION_P_H
