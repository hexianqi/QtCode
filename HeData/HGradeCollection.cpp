#include "HGradeCollection_p.h"
#include "IDataFactory.h"
#include "IFileStream.h"
#include "IGrade.h"
#include "HDataHelper.h"
#include "HeCore/HAppContext.h"

HE_DATA_BEGIN_NAMESPACE

HGradeCollectionPrivate::HGradeCollectionPrivate()
{
    factory = HAppContext::getContextPointer<IDataFactory>("IDataFactory");
    fileStream = factory->createFileStream("HFileStream");
    fileStream->setMagicNumber(0x00030001);
    fileStream->setFileVersion(0x01010101);
    fileStream->setFileFilter("Grade files (*.hcg)");
    fileStream->setReadContent([=](QDataStream &s) { readContent(s); });
    fileStream->setWriteContent([=](QDataStream &s) { writeContent(s); });
}

void HGradeCollectionPrivate::readContent(QDataStream &s)
{
    quint32 version;

    s >> version;
    HDataHelper::read<QString, HeData::IGrade>(s, datas, [=](QString type) { return factory->createGrade(type); });
    s >> useIndex;
}

void HGradeCollectionPrivate::writeContent(QDataStream &s)
{
    s << quint32(1);
    HDataHelper::write<QString, HeData::IGrade>(s, datas);
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
        text = new QString;
    auto i = item(useIndex());
    return i == nullptr ? -1 : i->calcLevel(value, text);
}

HE_DATA_END_NAMESPACE
