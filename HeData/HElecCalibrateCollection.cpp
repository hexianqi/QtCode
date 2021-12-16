#include "HElecCalibrateCollection_p.h"
#include "IDataFactory.h"
#include "IElecCalibrate.h"
#include "IDataStream.h"
#include "HStreamHelper.h"
#include "HeCore/HAppContext.h"

HE_BEGIN_NAMESPACE

HElecCalibrateCollectionPrivate::HElecCalibrateCollectionPrivate()
{
    factory = HAppContext::getContextPointer<IDataFactory>("IDataFactory");
    dataStream = factory->createDataStream("HDataStream");
    dataStream->setMagicNumber(0x00020002);
    dataStream->setFileVersion(0x01010101);
    dataStream->setFileFilter("Elec calibrate files (*.hce)");
    dataStream->setReadContent([=](QDataStream &s) { readContent(s); });
    dataStream->setWriteContent([=](QDataStream &s) { writeContent(s); });
}

void HElecCalibrateCollectionPrivate::readContent(QDataStream &s)
{
    quint32 version;
    s >> version;
    HStreamHelper::read<QString, IElecCalibrate>(s, items, [=](QString type) { return factory->createElecCalibrate(type); });
}

void HElecCalibrateCollectionPrivate::writeContent(QDataStream &s)
{
    s << quint32(1);
    HStreamHelper::write<QString, IElecCalibrate>(s, items);
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

IDataStream *HElecCalibrateCollection::dataStream()
{
    Q_D(HElecCalibrateCollection);
    return d->dataStream;
}

HE_END_NAMESPACE
