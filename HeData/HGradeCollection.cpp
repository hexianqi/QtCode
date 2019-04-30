#include "HGradeCollection_p.h"
#include "IDataFactory.h"
#include "IFileStream.h"
#include "IGrade.h"
#include <QtCore/QDataStream>

HE_DATA_BEGIN_NAMESPACE

HGradeCollectionPrivate::HGradeCollectionPrivate(IDataFactory *f)
{
    factory = f;
    fileStream = f->createFileStream("HFileStream");
    fileStream->setMagicNumber(0x00030001);
    fileStream->setFileVersion(0x01010101);
    fileStream->setFileFilter("Grade files (*.hcg)");
    fileStream->setReadContent([=](QDataStream &s) { readContent(s); });
    fileStream->setWriteContent([=](QDataStream &s) { writeContent(s); });
}

void HGradeCollectionPrivate::readContent(QDataStream &s)
{
    quint32 version;
    quint32 size;
    QString key, type;

    datas.clear();
    s >> version;
    s >> size;
    for (quint32 i = 0; i < size; i++)
    {
        s >> key >> type;
        auto item = factory->createGrade(type);
        item->readContent(s, factory);
        if (s.status() != QDataStream::Ok)
        {
            datas.clear();
            break;
        }
        datas.insert(key, item);
    }
    s >> useIndex;
}

void HGradeCollectionPrivate::writeContent(QDataStream &s)
{
    s << quint32(1);
    s << quint32(datas.size());
    for (auto i = datas.begin(); i != datas.end(); i++)
    {
        s << i.key() << i.value()->typeName();
        i.value()->writeContent(s);
    }
    s << useIndex;
}

HGradeCollection::HGradeCollection(IDataFactory *f) :
    IGradeCollection(*new HGradeCollectionPrivate(f))
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

IFileStream *HGradeCollection::fileStream()
{
    Q_D(HGradeCollection);
    return d->fileStream;
}

void HGradeCollection::setUseIndex(QString value)
{
    Q_D(HGradeCollection);
    if (d->useIndex == value || !contains(value))
        return;
    d->useIndex = value;
}

QString HGradeCollection::useIndex()
{
    Q_D(HGradeCollection);
    return d->useIndex;
}

QVariant HGradeCollection::levels(QString type)
{
    auto i = item(useIndex());
    return i == nullptr ? QVariant() : i->levels(type);
}

int HGradeCollection::calcLevel(QVariantMap value, QString &text)
{
    auto i = item(useIndex());
    return i == nullptr ? -1 : i->calcLevel(value, text);
}

HE_DATA_END_NAMESPACE
