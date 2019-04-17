#include "HThreadCollection_p.h"

HE_CONTROLLER_BEGIN_NAMESPACE

HThreadCollection::HThreadCollection() :
    HCollection<IThread>(*new HThreadCollectionPrivate)
{
}

HThreadCollection::HThreadCollection(HThreadCollectionPrivate &p) :
    HCollection<IThread>(p)
{
}

HThreadCollection::~HThreadCollection()
{
}

QString HThreadCollection::typeName()
{
    return "HThreadCollection";
}

HE_CONTROLLER_END_NAMESPACE
