#include "HAdjustCollection_p.h"
#include "IDataFactory.h"
#include "IAdjust.h"
#include "IDataStream.h"
#include "IMultStream.h"
#include "HStreamHelper.h"
#include "HeCore/HAppContext.h"

HE_DATA_BEGIN_NAMESPACE

HAdjustCollectionPrivate::HAdjustCollectionPrivate()
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

void HAdjustCollectionPrivate::readContent(QDataStream &s)
{
    quint32 version;

    s >> version;
    HStreamHelper::read<QString, HeData::IAdjust>(s, datas, [=](QString type) { return factory->createAdjust(type); });
    s >> useIndex;
}

void HAdjustCollectionPrivate::writeContent(QDataStream &s)
{
    s << quint32(1);
    HStreamHelper::write<QString, HeData::IAdjust>(s, datas);
    s << useIndex;
}

HAdjustCollection::HAdjustCollection() :
    IAdjustCollection(*new HAdjustCollectionPrivate)
{
}

HAdjustCollection::HAdjustCollection(HAdjustCollectionPrivate &p) :
    IAdjustCollection(p)
{
}

QString HAdjustCollection::typeName()
{
    return "HAdjustCollection";
}

QVariantMap HAdjustCollection::correct(QVariantMap value)
{
    auto i = item(useIndex());
    return i == nullptr ? QVariantMap() : i->correct(value);
}

HE_DATA_END_NAMESPACE
