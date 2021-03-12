#pragma once

#include "HDeviceCollection.h"
#include <QtCore/QSet>

HE_COMMUNICATE_BEGIN_NAMESPACE

class HDeviceCollectionPrivate : public HCollectionPrivate<IDevice>
{
public:
    QSet<HActionType> additionals;
};

HE_COMMUNICATE_END_NAMESPACE
