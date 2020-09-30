#include "HSpecCalibrateCollection_p.h"
#include "IDataFactory.h"
#include "ISpecCalibrate.h"
#include "IDataStream.h"
#include "HStreamHelper.h"
#include "HeCore/HAppContext.h"

HE_DATA_BEGIN_NAMESPACE

HSpecCalibrateCollectionPrivate::HSpecCalibrateCollectionPrivate()
{
    factory = HAppContext::getContextPointer<IDataFactory>("IDataFactory");
    dataStream = factory->createDataStream("HDataStream");
    dataStream->setMagicNumber(0x00020001);
    dataStream->setFileVersion(0x01010101);
    dataStream->setFileFilter("Spec calibrate files (*.hcs)");
    dataStream->setReadContent([=](QDataStream &s) { readContent(s); });
    dataStream->setWriteContent([=](QDataStream &s) { writeContent(s); });
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

QString HSpecCalibrateCollection::typeName()
{
    return "HSpecCalibrateCollection";
}

IDataStream *HSpecCalibrateCollection::dataStream()
{
    Q_D(HSpecCalibrateCollection);
    return d->dataStream;
}

HE_DATA_END_NAMESPACE
