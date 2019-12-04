#include "HProtocolCollection_p.h"
#include <QtCore/QDebug>

HE_COMMUNICATE_BEGIN_NAMESPACE

HProtocolCollection::HProtocolCollection() :
    IProtocolCollection(*new HProtocolCollectionPrivate)
{
}

HProtocolCollection::HProtocolCollection(HProtocolCollectionPrivate &p) :
    IProtocolCollection(p)
{
}

HProtocolCollection::~HProtocolCollection()
{
    qDebug() << __func__;
}

QString HProtocolCollection::typeName()
{
    return "HProtocolCollection";
}

HE_COMMUNICATE_END_NAMESPACE
