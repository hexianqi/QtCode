#include "HQualityCollection_p.h"
#include "IDataFactory.h"
#include "IQuality.h"
#include "IDataStream.h"
#include "IMultStream.h"
#include "HStreamHelper.h"
#include "HeCore/HAppContext.h"
#include <QtGui/QColor>

HE_BEGIN_NAMESPACE

HQualityCollectionPrivate::HQualityCollectionPrivate()
{
    factory = HAppContext::getContextPointer<IDataFactory>("IDataFactory");
    dataStream = factory->createDataStream("HDataStream");
    dataStream->setMagicNumber(0x00030101);
    dataStream->setFileVersion(0x01010101);
    dataStream->setFileFilter("Quality files (*.hcq)");
    dataStream->setReadContent([=](QDataStream &s) { readContent(s); });
    dataStream->setWriteContent([=](QDataStream &s) { writeContent(s); });
    multStream = factory->createMultStream("HMultStream");
    multStream->addStream("hcq", dataStream);
}

void HQualityCollectionPrivate::readContent(QDataStream &s)
{
    quint32 version;

    s >> version;
    HStreamHelper::read<QString, IQuality>(s, items, [=](QString type) { return factory->createQuality(type); });
    s >> useIndex;
}

void HQualityCollectionPrivate::writeContent(QDataStream &s)
{
    s << quint32(1);
    HStreamHelper::write<QString, IQuality>(s, items);
    s << useIndex;
}

HQualityCollection::HQualityCollection() :
    IQualityCollection(*new HQualityCollectionPrivate)
{
}

HQualityCollection::HQualityCollection(HQualityCollectionPrivate &p) :
    IQualityCollection(p)
{
}

HQualityCollection::~HQualityCollection() = default;

QString HQualityCollection::typeName()
{
    return "HQualityCollection";
}

HQualityReport HQualityCollection::check(QVariantMap value, QVariantMap *color)
{
    if (color == nullptr)
        color = new QVariantMap();
    color->clear();
    auto i = item(useIndex());
    return i == nullptr ? HQualityReport::InvalidQuality : i->check(value, color);
}

QColor HQualityCollection::color(HQualityReport type)
{
    auto i = item(useIndex());
    return i == nullptr ? Qt::transparent : i->color(type);
}

double HQualityCollection::drift(QString type, QVariant value)
{
    auto i = item(useIndex());
    return i == nullptr ? 0 : i->drift(type, value);
}

HE_END_NAMESPACE
