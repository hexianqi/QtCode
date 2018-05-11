#include "HDeviceCollection_p.h"
#include "IDevice.h"

HE_COMMUNICATE_USE_NAMESPACE

HDeviceCollection::HDeviceCollection(HDeviceCollectionPrivate &p)
    : d_ptr(&p)
{
}

bool HeCommunicate::HDeviceCollection::isSupport(HActionType action)
{
    if (d_ptr->additionals.contains(action))
        return true;

    for (auto v : this->values())
    {
        if (v->isSupport(action))
            return true;
    }
    return false;
}
