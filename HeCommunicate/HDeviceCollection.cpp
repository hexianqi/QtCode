#include "HDeviceCollection_p.h"
#include "IDevice.h"

HE_COMMUNICATE_BEGIN_NAMESPACE

HDeviceCollection::HDeviceCollection() :
    IDeviceCollection(*new HDeviceCollectionPrivate)
{
}

HDeviceCollection::HDeviceCollection(HDeviceCollectionPrivate &p) :
    IDeviceCollection(p)
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
    Q_D(HDeviceCollection);
    d->additionals.insert(action);
}

bool HDeviceCollection::isSupport(HActionType action)
{
    Q_D(HDeviceCollection);
    if (d->additionals.contains(action))
        return true;
    for (auto v : d->datas)
    {
        if (v->isSupport(action))
            return true;
    }
    return false;
}

HE_COMMUNICATE_END_NAMESPACE
