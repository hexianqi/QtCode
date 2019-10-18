#include "HElecCalibrateCollection_p.h"
#include "IDataFactory.h"
#include "IElecCalibrate.h"
#include "IFileStream.h"
#include "HDataHelper.h"
#include "HeCore/HAppContext.h"

HE_DATA_BEGIN_NAMESPACE

HElecCalibrateCollectionPrivate::HElecCalibrateCollectionPrivate()
{
    factory = HAppContext::getContextPointer<IDataFactory>("IDataFactory");
    fileStream = factory->createFileStream("HFileStream");
    fileStream->setMagicNumber(0x00020002);
    fileStream->setFileVersion(0x01010101);
    fileStream->setFileFilter("Elec calibrate files (*.hce)");
    fileStream->setReadContent([=](QDataStream &s) { readContent(s); });
    fileStream->setWriteContent([=](QDataStream &s) { writeContent(s); });
}

void HElecCalibrateCollectionPrivate::readContent(QDataStream &s)
{
    quint32 version;

    s >> version;
    HDataHelper::read<QString, HeData::IElecCalibrate>(s, datas, [=](QString type) { return factory->createElecCalibrate(type); });
}

void HElecCalibrateCollectionPrivate::writeContent(QDataStream &s)
{
    s << quint32(1);
    HDataHelper::write<QString, HeData::IElecCalibrate>(s, datas);
}

HElecCalibrateCollection::HElecCalibrateCollection() :
    IElecCalibrateCollection(*new HElecCalibrateCollectionPrivate)
{
}

HElecCalibrateCollection::HElecCalibrateCollection(HElecCalibrateCollectionPrivate &p) :
    IElecCalibrateCollection(p)
{
}

HElecCalibrateCollection::~HElecCalibrateCollection()
{
}

QString HElecCalibrateCollection::typeName()
{
    return "HElecCalibrateCollection";
}

IFileStream *HElecCalibrateCollection::fileStream()
{
    Q_D(HElecCalibrateCollection);
    return d->fileStream;
}

HE_DATA_END_NAMESPACE
