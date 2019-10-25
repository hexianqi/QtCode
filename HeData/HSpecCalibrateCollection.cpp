#include "HSpecCalibrateCollection_p.h"
#include "IDataFactory.h"
#include "ISpecCalibrate.h"
#include "IFileStream.h"
#include "HStreamHelper.h"
#include "HeCore/HAppContext.h"

HE_DATA_BEGIN_NAMESPACE

HSpecCalibrateCollectionPrivate::HSpecCalibrateCollectionPrivate()
{
    factory = HAppContext::getContextPointer<IDataFactory>("IDataFactory");
    fileStream = factory->createFileStream("HFileStream");
    fileStream->setMagicNumber(0x00020001);
    fileStream->setFileVersion(0x01010101);
    fileStream->setFileFilter("Spec calibrate files (*.hcs)");
    fileStream->setReadContent([=](QDataStream &s) { readContent(s); });
    fileStream->setWriteContent([=](QDataStream &s) { writeContent(s); });
}

void HSpecCalibrateCollectionPrivate::readContent(QDataStream &s)
{
    quint32 version;

    s >> version;
    HStreamHelper::read<QString, HeData::ISpecCalibrate>(s, datas, [=](QString type) { return factory->createSpecCalibrate(type); });
}

void HSpecCalibrateCollectionPrivate::writeContent(QDataStream &s)
{
    s << quint32(1);
    HStreamHelper::write<QString, HeData::ISpecCalibrate>(s, datas);
}

HSpecCalibrateCollection::HSpecCalibrateCollection() :
    ISpecCalibrateCollection(*new HSpecCalibrateCollectionPrivate)
{
}

HSpecCalibrateCollection::HSpecCalibrateCollection(HSpecCalibrateCollectionPrivate &p) :
    ISpecCalibrateCollection(p)
{
}

HSpecCalibrateCollection::~HSpecCalibrateCollection()
{
}

QString HSpecCalibrateCollection::typeName()
{
    return "HSpecCalibrateCollection";
}

IFileStream *HSpecCalibrateCollection::fileStream()
{
    Q_D(HSpecCalibrateCollection);
    return d->fileStream;
}

HE_DATA_END_NAMESPACE
