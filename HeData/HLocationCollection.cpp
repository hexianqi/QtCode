#include "HLocationCollection_p.h"
#include "IDataFactory.h"
#include "IDataStream.h"
#include "IMultStream.h"
#include "ILocation.h"
#include "HStreamHelper.h"
#include "HeCore/HAppContext.h"
#include <QtGui/QPolygon>

HE_BEGIN_NAMESPACE

HLocationCollectionPrivate::HLocationCollectionPrivate()
{
    factory = HAppContext::getContextPointer<IDataFactory>("IDataFactory");
    dataStream = factory->createDataStream("HDataStream");
    dataStream->setMagicNumber(0x00031001);
    dataStream->setFileVersion(0x01010101);
    dataStream->setFileFilter("Location files (*.hco)");
    dataStream->setReadContent([=](QDataStream &s) { readContent(s); });
    dataStream->setWriteContent([=](QDataStream &s) { writeContent(s); });
    multStream = factory->createMultStream("HMultStream");
    multStream->addStream("hco", dataStream);
}

void HLocationCollectionPrivate::readContent(QDataStream &s)
{
    quint32 version;

    s >> version;
    HStreamHelper::read<QString, ILocation>(s, items, [=](QString type) { return factory->createLocation(type); });
    s >> useIndex;
}

void HLocationCollectionPrivate::writeContent(QDataStream &s)
{
    s << quint32(1);
    HStreamHelper::write<QString, ILocation>(s, items);
    s << useIndex;
}


HLocationCollection::HLocationCollection() :
    ILocationCollection(*new HLocationCollectionPrivate)
{
}

HLocationCollection::HLocationCollection(HLocationCollectionPrivate &p) :
    ILocationCollection(p)
{
}

HLocationCollection::~HLocationCollection() = default;

QString HLocationCollection::typeName()
{
    return "HLocationCollection";
}

QPolygon HLocationCollection::polygon()
{
    auto i = useItem();
    return i == nullptr ? QPolygon() : i->polygon();
}

HE_END_NAMESPACE
