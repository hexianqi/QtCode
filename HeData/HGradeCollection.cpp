#include "HGradeCollection_p.h"
#include "IDataFactory.h"
#include "IDataStream.h"
#include "IMultStream.h"
#include "IGrade.h"
#include "HStreamHelper.h"
#include "HeCore/HAppContext.h"

HE_DATA_BEGIN_NAMESPACE

HGradeCollectionPrivate::HGradeCollectionPrivate()
{
    factory = HAppContext::getContextPointer<IDataFactory>("IDataFactory");
    dataStream = factory->createDataStream("HDataStream");
    dataStream->setMagicNumber(0x00030001);
    dataStream->setFileVersion(0x01010101);
    dataStream->setFileFilter("Grade files (*.hcg)");
    dataStream->setReadContent([=](QDataStream &s) { readContent(s); });
    dataStream->setWriteContent([=](QDataStream &s) { writeContent(s); });
    multStream = factory->createMultStream("HMultStream");
    multStream->addStream("hcg", dataStream);
}

void HGradeCollectionPrivate::readContent(QDataStream &s)
{
    quint32 version;

    s >> version;
    HStreamHelper::read<QString, HeData::IGrade>(s, items, [=](QString type) { return factory->createGrade(type); });
    s >> useIndex;
}

void HGradeCollectionPrivate::writeContent(QDataStream &s)
{
    s << quint32(1);
    HStreamHelper::write<QString, HeData::IGrade>(s, items);
    s << useIndex;
}

HGradeCollection::HGradeCollection() :
    IGradeCollection(*new HGradeCollectionPrivate)
{
}

HGradeCollection::HGradeCollection(HGradeCollectionPrivate &p) :
    IGradeCollection(p)
{
}

HGradeCollection::~HGradeCollection()
{
}

QString HGradeCollection::typeName()
{
    return "HGradeCollection";
}

QVariant HGradeCollection::levels(QString type)
{
    auto i = item(useIndex());
    return i == nullptr ? QVariant() : i->levels(type);
}

int HGradeCollection::calcLevel(QVariantMap value, QString *text)
{
    if (text == nullptr)
        text = new QString();
    auto i = item(useIndex());
    return i == nullptr ? -1 : i->calcLevel(value, text);
}

HE_DATA_END_NAMESPACE
