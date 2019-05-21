#include "HChromatismCollection_p.h"
#include "IDataFactory.h"
#include "IChromatism.h"
#include "IFileStream.h"
#include <QtCore/QDataStream>
#include <QtCore/QPointF>
#include <QtCore/QJsonObject>

HE_DATA_BEGIN_NAMESPACE

HChromatismCollectionPrivate::HChromatismCollectionPrivate(IDataFactory *f)
{
    factory = f;
    fileStream = f->createFileStream("HFileStream");
    fileStream->setMagicNumber(0x00020101);
    fileStream->setFileVersion(0x01010101);
    fileStream->setFileFilter("Chromatism files (*.hcc)");
    fileStream->setReadContent([=](QDataStream &s) { readContent(s); });
    fileStream->setWriteContent([=](QDataStream &s) { writeContent(s); });
}

void HChromatismCollectionPrivate::readContent(QDataStream &s)
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
        auto item = factory->createChromatism(type);
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

void HChromatismCollectionPrivate::writeContent(QDataStream &s)
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

HChromatismCollection::HChromatismCollection(IDataFactory *f) :
    IChromatismCollection(*new HChromatismCollectionPrivate(f))
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

IFileStream *HChromatismCollection::fileStream()
{
    Q_D(HChromatismCollection);
    return d->fileStream;
}

void HChromatismCollection::setUseIndex(QString value)
{
    Q_D(HChromatismCollection);
    if (d->useIndex == value || !contains(value))
        return;
    d->useIndex = value;
}

QString HChromatismCollection::useIndex()
{
    Q_D(HChromatismCollection);
    return d->useIndex;
}

double HChromatismCollection::calcSdcm(double tc, QPointF xy)
{
    auto i = item(useIndex());
    return i == nullptr ? 0 : i->calcSdcm(tc, xy);
}

QJsonObject HChromatismCollection::toJson()
{
    auto i = item(useIndex());
    return i == nullptr ? QJsonObject() : i->toJson();
}

HE_DATA_END_NAMESPACE
