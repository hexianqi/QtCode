#include "HLuminousCalibrateCollection_p.h"
#include "IDataFactory.h"
#include "ILuminousCalibrate.h"
#include "IFileStream.h"
#include "HStreamHelper.h"
#include "HeCore/HAppContext.h"

HE_DATA_BEGIN_NAMESPACE

HLuminousCalibrateCollectionPrivate::HLuminousCalibrateCollectionPrivate()
{
    factory = HAppContext::getContextPointer<IDataFactory>("IDataFactory");
    fileStream = factory->createFileStream("HFileStream");
    fileStream->setMagicNumber(0x00020003);
    fileStream->setFileVersion(0x01010101);
    fileStream->setFileFilter("Luminous calibrate files (*.hcl)");
    fileStream->setReadContent([=](QDataStream &s) { readContent(s); });
    fileStream->setWriteContent([=](QDataStream &s) { writeContent(s); });
}

void HLuminousCalibrateCollectionPrivate::readContent(QDataStream &s)
{
    quint32 version;
    s >> version;
    HStreamHelper::read<QString, HeData::ILuminousCalibrate>(s, datas, [=](QString type) { return factory->createLuminousCalibrate(type); });
}

void HLuminousCalibrateCollectionPrivate::writeContent(QDataStream &s)
{
    s << quint32(1);
    HStreamHelper::write<QString, HeData::ILuminousCalibrate>(s, datas);
}

HLuminousCalibrateCollection::HLuminousCalibrateCollection() :
    ILuminousCalibrateCollection(*new HLuminousCalibrateCollectionPrivate)
{
}

HLuminousCalibrateCollection::HLuminousCalibrateCollection(HLuminousCalibrateCollectionPrivate &p) :
    ILuminousCalibrateCollection(p)
{
}

QString HLuminousCalibrateCollection::typeName()
{
    return "HLuminousCalibrateCollection";
}

IFileStream *HLuminousCalibrateCollection::fileStream()
{
    Q_D(HLuminousCalibrateCollection);
    return d->fileStream;
}

HE_DATA_END_NAMESPACE
