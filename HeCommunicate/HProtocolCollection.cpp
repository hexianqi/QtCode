#include "HProtocolCollection_p.h"

HE_COMMUNICATE_BEGIN_NAMESPACE

HProtocolCollection::HProtocolCollection()
    :  d_ptr(new HProtocolCollectionPrivate)
{
}

HProtocolCollection::HProtocolCollection(HProtocolCollectionPrivate &p)
    : d_ptr(&p)
{
}

HProtocolCollection::~HProtocolCollection()
{
}

HE_COMMUNICATE_END_NAMESPACE
