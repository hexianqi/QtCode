#include "HThreadCollection_p.h"

HE_CONTROLLER_BEGIN_NAMESPACE

HThreadCollection::HThreadCollection()
    :  d_ptr(new HThreadCollectionPrivate)
{
}

HThreadCollection::HThreadCollection(HThreadCollectionPrivate &p)
    : d_ptr(&p)
{
}

HThreadCollection::~HThreadCollection()
{
}

HE_CONTROLLER_END_NAMESPACE
