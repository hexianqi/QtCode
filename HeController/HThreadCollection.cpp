#include "HThreadCollection_p.h"

HE_BEGIN_NAMESPACE

HThreadCollection::HThreadCollection() :
    IThreadCollection(*new HThreadCollectionPrivate)
{
}

HThreadCollection::HThreadCollection(HThreadCollectionPrivate &p) :
    IThreadCollection(p)
{
}

HThreadCollection::~HThreadCollection() = default;

QString HThreadCollection::typeName()
{
    return "HThreadCollection";
}

HE_END_NAMESPACE
