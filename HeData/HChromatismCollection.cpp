#include "HChromatismCollection_p.h"
#include "IDataFactory.h"
#include "IChromatism.h"
#include "IDataStream.h"
#include "IMultStream.h"
#include "HStreamHelper.h"
#include "HeCore/HAppContext.h"
#include <QtCore/QPointF>

HE_BEGIN_NAMESPACE

HChromatismCollectionPrivate::HChromatismCollectionPrivate()
{
    factory = HAppContext::getContextPointer<IDataFactory>("IDataFactory");
    dataStream = factory->createDataStream("HDataStream");
    dataStream->setMagicNumber(0x00020101);
    dataStream->setFileVersion(0x01010101);
    dataStream->setFileFilter("Chromatism files (*.hcc)");
    dataStream->setReadContent([=](QDataStream &s) { readContent(s); });
    dataStream->setWriteContent([=](QDataStream &s) { writeContent(s); });
    multStream = factory->createMultStream("HMultStream");
    multStream->addStream("hcc", dataStream);
}

void HChromatismCollectionPrivate::readContent(QDataStream &s)
{
    quint32 version;

    s >> version;
    HStreamHelper::read<QString, IChromatism>(s, items, [=](QString type) { return factory->createChromatism(type); });
    s >> useIndex;
}

void HChromatismCollectionPrivate::writeContent(QDataStream &s)
{
    s << quint32(1);
    HStreamHelper::write<QString, IChromatism>(s, items);
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

HChromatismCollection::~HChromatismCollection()
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

QVariantMap HChromatismCollection::detail()
{
    auto i = item(useIndex());
    return i == nullptr ? QVariantMap() : i->detail();
}

HE_END_NAMESPACE
