#include "HLuminousCalibrateCollection_p.h"
#include "IDataFactory.h"
#include "ILuminousCalibrate.h"
#include "IDataStream.h"
#include "HStreamHelper.h"
#include "HeCore/HAppContext.h"

HE_DATA_BEGIN_NAMESPACE

HLuminousCalibrateCollectionPrivate::HLuminousCalibrateCollectionPrivate()
{
    factory = HAppContext::getContextPointer<IDataFactory>("IDataFactory");
    dataStream = factory->createDataStream("HDataStream");
    dataStream->setMagicNumber(0x00020003);
    dataStream->setFileVersion(0x01010101);
    dataStream->setFileFilter("Luminous calibrate files (*.hcl)");
    dataStream->setReadContent([=](QDataStream &s) { readContent(s); });
    dataStream->setWriteContent([=](QDataStream &s) { writeContent(s); });
}

void HLuminousCalibrateCollectionPrivate::readContent(QDataStream &s)
{
    quint32 version;
    s >> version;
    HStreamHelper::read<QString, HeData::ILuminousCalibrate>(s, items, [=](QString type) { return factory->createLuminousCalibrate(type); });
}

void HLuminousCalibrateCollectionPrivate::writeContent(QDataStream &s)
{
    s << quint32(1);
    HStreamHelper::write<QString, HeData::ILuminousCalibrate>(s, items);
}

HLuminousCalibrateCollection::HLuminousCalibrateCollection() :
    ILuminousCalibrateCollection(*new HLuminousCalibrateCollectionPrivate)
{
}

HLuminousCalibrateCollection::HLuminousCalibrateCollection(HLuminousCalibrateCollectionPrivate &p) :
    ILuminousCalibrateCollection(p)
{
}

HLuminousCalibrateCollection::~HLuminousCalibrateCollection()
{
}

QString HLuminousCalibrateCollection::typeName()
{
    return "HLuminousCalibrateCollection";
}

IDataStream *HLuminousCalibrateCollection::dataStream()
{
    Q_D(HLuminousCalibrateCollection);
    return d->dataStream;
}

HE_DATA_END_NAMESPACE
