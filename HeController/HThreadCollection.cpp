#include "HThreadCollection_p.h"
#include <QtCore/QDebug>

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
    qDebug() << __func__;
}

QString HThreadCollection::typeName()
{
    return "HThreadCollection";
}

HE_CONTROLLER_END_NAMESPACE
