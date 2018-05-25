#include "HDeviceCollection_p.h"
#include "IDevice.h"

HE_COMMUNICATE_BEGIN_NAMESPACE

HDeviceCollection::HDeviceCollection()
    :  d_ptr(new HDeviceCollectionPrivate)
{
}

HDeviceCollection::HDeviceCollection(HDeviceCollectionPrivate &p)
    : d_ptr(&p)
{
}

HDeviceCollection::~HDeviceCollection()
{
}

void HDeviceCollection::initialize(QVariantMap param)
{
    HCollection<IDevice>::initialize(param);
    if (param.contains("supports"))
    {
        for (auto v : param.value("supports").toList())
            addSupport(v.toLongLong());
    }
}

QString HDeviceCollection::typeName()
{
    return "HDeviceCollection";
}

void HDeviceCollection::addSupport(HActionType action)
{
    d_ptr->additionals.insert(action);
}

bool HDeviceCollection::isSupport(HActionType action)
{
    if (d_ptr->additionals.contains(action))
        return true;

    for (auto v : _datas->values())
    {
        if (v->isSupport(action))
            return true;
    }
    return false;
}

HE_COMMUNICATE_END_NAMESPACE
