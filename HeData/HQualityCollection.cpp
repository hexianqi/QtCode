#include "HQualityCollection_p.h"
#include "IDataFactory.h"
#include "IQuality.h"
#include "IFileStream.h"
#include <QtGui/QColor>
#include <QtCore/QDataStream>

HE_DATA_BEGIN_NAMESPACE

HQualityCollectionPrivate::HQualityCollectionPrivate(IDataFactory *f)
{
    factory = f;
    fileStream = f->createFileStream("HFileStream");
    fileStream->setMagicNumber(0x00030101);
    fileStream->setFileVersion(0x01010101);
    fileStream->setFileFilter("Adjust files (*.hca)");
    fileStream->setReadContent([=](QDataStream &s) { readContent(s); });
    fileStream->setWriteContent([=](QDataStream &s) { writeContent(s); });
}

void HQualityCollectionPrivate::readContent(QDataStream &s)
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
        auto item = factory->createQuality(type);
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

void HQualityCollectionPrivate::writeContent(QDataStream &s)
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

HQualityCollection::HQualityCollection(IDataFactory *f) :
    IQualityCollection(*new HQualityCollectionPrivate(f))
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

IFileStream *HQualityCollection::fileStream()
{
    Q_D(HQualityCollection);
    return d->fileStream;
}

void HQualityCollection::setUseIndex(QString value)
{
    Q_D(HQualityCollection);
    if (d->useIndex == value || !contains(value))
        return;
    d->useIndex = value;
}

QString HQualityCollection::useIndex()
{
    Q_D(HQualityCollection);
    return d->useIndex;
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
