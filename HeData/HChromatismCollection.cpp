#include "HChromatismCollection_p.h"
#include "IDataFactory.h"
#include "IChromatism.h"
#include "IFileStream.h"
#include "HStreamHelper.h"
#include "HeCore/HAppContext.h"
#include <QtCore/QPointF>

HE_DATA_BEGIN_NAMESPACE

HChromatismCollectionPrivate::HChromatismCollectionPrivate()
{
    factory = HAppContext::getContextPointer<IDataFactory>("IDataFactory");
    fileStream = factory->createFileStream("HFileStream");
    fileStream->setMagicNumber(0x00020101);
    fileStream->setFileVersion(0x01010101);
    fileStream->setFileFilter("Chromatism files (*.hcc)");
    fileStream->setReadContent([=](QDataStream &s) { readContent(s); });
    fileStream->setWriteContent([=](QDataStream &s) { writeContent(s); });
}

void HChromatismCollectionPrivate::readContent(QDataStream &s)
{
    quint32 version;

    s >> version;
    HStreamHelper::read<QString, HeData::IChromatism>(s, datas, [=](QString type) { return factory->createChromatism(type); });
    s >> useIndex;
}

void HChromatismCollectionPrivate::writeContent(QDataStream &s)
{
    s << quint32(1);
    HStreamHelper::write<QString, HeData::IChromatism>(s, datas);
    s << useIndex;
}

HChromatismCollection::HChromatismCollection() :
    IChromatismCollection(*new HChromatismCollectionPrivate)
{
}

HChromatismCollection::HChromatismCollection(HChromatismCollectionPrivate &p) :
    IChromatismCollection(p)
{
}

QString HChromatismCollection::typeName()
{
    return "HChromatismCollection";
}

double HChromatismCollection::calcSdcm(double tc, QPointF xy)
{
    auto i = item(useIndex());
    return i == nullptr ? 0 : i->calcSdcm(tc, xy);
}

QVariantMap HChromatismCollection::toMap()
{
    auto i = item(useIndex());
    return i == nullptr ? QVariantMap() : i->toMap();
}

HE_DATA_END_NAMESPACE
