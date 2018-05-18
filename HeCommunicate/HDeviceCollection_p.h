#ifndef HDEVICECOLLECTION_P_H
#define HDEVICECOLLECTION_P_H

#include "HDeviceCollection.h"
#include <QSet>

HE_COMMUNICATE_BEGIN_NAMESPACE

class HDeviceCollectionPrivate
{
public:
    QSet<HActionType> additionals;
};

HE_COMMUNICATE_END_NAMESPACE

#endif // HDEVICECOLLECTION_P_H
