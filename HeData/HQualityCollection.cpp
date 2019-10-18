#include "HQualityCollection_p.h"
#include "IDataFactory.h"
#include "IQuality.h"
#include "IFileStream.h"
#include "HDataHelper.h"
#include "HeCore/HAppContext.h"
#include <QtGui/QColor>

HE_DATA_BEGIN_NAMESPACE

HQualityCollectionPrivate::HQualityCollectionPrivate()
{
    factory = HAppContext::getContextPointer<IDataFactory>("IDataFactory");
    fileStream = factory->createFileStream("HFileStream");
    fileStream->setMagicNumber(0x00030101);
    fileStream->setFileVersion(0x01010101);
    fileStream->setFileFilter("Quality files (*.hcq)");
    fileStream->setReadContent([=](QDataStream &s) { readContent(s); });
    fileStream->setWriteContent([=](QDataStream &s) { writeContent(s); });
}

void HQualityCollectionPrivate::readContent(QDataStream &s)
{
    quint32 version;

    s >> version;
    HDataHelper::read<QString, HeData::IQuality>(s, datas, [=](QString type) { return factory->createQuality(type); });
    s >> useIndex;
}

void HQualityCollectionPrivate::writeContent(QDataStream &s)
{
    s << quint32(1);
    HDataHelper::write<QString, HeData::IQuality>(s, datas);
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

HQualityCollection::~HQualityCollection()
{
}

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

QColor HQualityCollection::color(HQualityReport value)
{
    auto i = item(useIndex());
    return i == nullptr ? Qt::transparent : i->color(value);
}

double HQualityCollection::drift(QString type, QVariant value)
{
    auto i = item(useIndex());
    return i == nullptr ? 0 : i->drift(type, value);
}

HE_DATA_END_NAMESPACE
