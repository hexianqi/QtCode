#include "HProtocolCollection_p.h"

HE_BEGIN_NAMESPACE

HProtocolCollection::HProtocolCollection() :
    IProtocolCollection(*new HProtocolCollectionPrivate)
{
}

HProtocolCollection::HProtocolCollection(HProtocolCollectionPrivate &p) :
    IProtocolCollection(p)
{
}

HProtocolCollection::~HProtocolCollection() = default;

QString HProtocolCollection::typeName()
{
    return "HProtocolCollection";
}

HE_END_NAMESPACE
