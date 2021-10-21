#include "HAdjust2Collection_p.h"
#include "IDataFactory.h"
#include "IDataStream.h"
#include "IMultStream.h"
#include "IAdjust2.h"
#include "HStreamHelper.h"
#include "HeCore/HAppContext.h"

HE_DATA_BEGIN_NAMESPACE

HAdjust2CollectionPrivate::HAdjust2CollectionPrivate()
{
    factory = HAppContext::getContextPointer<IDataFactory>("IDataFactory");
    dataStream = factory->createDataStream("HDataStream");
    dataStream->setMagicNumber(0x00040001);
    dataStream->setFileVersion(0x01010101);
    dataStream->setFileFilter("Adjust files (*.hca)");
    dataStream->setReadContent([=](QDataStream &s) { readContent(s); });
    dataStream->setWriteContent([=](QDataStream &s) { writeContent(s); });
    multStream = factory->createMultStream("HMultStream");
    multStream->addStream("hca", dataStream);
}

void HAdjust2CollectionPrivate::readContent(QDataStream &s)
{
    quint32 version;
    s >> version;
    HStreamHelper::read<QString, HeData::IAdjust2>(s, items, [=](QString type) { return factory->createAdjust2(type); });
    s >> useIndex;
}

void HAdjust2CollectionPrivate::writeContent(QDataStream &s)
{
    s << quint32(1);
    HStreamHelper::write<QString, HeData::IAdjust2>(s, items);
    s << useIndex;
}

HAdjust2Collection::HAdjust2Collection() :
    IAdjust2Collection(*new HAdjust2CollectionPrivate)
{
}

HAdjust2Collection::HAdjust2Collection(HAdjust2CollectionPrivate &p) :
    IAdjust2Collection(p)
{
}

HAdjust2Collection::~HAdjust2Collection()
{
}

QString HAdjust2Collection::typeName()
{
    return "HAdjust2Collection";
}

QVariantMap HAdjust2Collection::correct(double tc, QVariantMap value)
{
    auto i = item(useIndex());
    return i == nullptr ? QVariantMap() : i->correct(tc, value);
}

HE_DATA_END_NAMESPACE
