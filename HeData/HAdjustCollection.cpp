#include "HAdjustCollection_p.h"
#include "IDataFactory.h"
#include "IAdjust.h"
#include "IFileStream.h"
#include <QtCore/QDataStream>

HE_DATA_BEGIN_NAMESPACE

HAdjustCollectionPrivate::HAdjustCollectionPrivate(IDataFactory *f)
{
    factory = f;
    fileStream = f->createFileStream("HFileStream");
    fileStream->setMagicNumber(0x00040001);
    fileStream->setFileVersion(0x01010101);
    fileStream->setFileFilter("Adjust files (*.hca)");
    fileStream->setReadContent([=](QDataStream &s) { readContent(s); });
    fileStream->setWriteContent([=](QDataStream &s) { writeContent(s); });
}

void HAdjustCollectionPrivate::readContent(QDataStream &s)
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
        auto item = factory->createAdjust(type);
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

void HAdjustCollectionPrivate::writeContent(QDataStream &s)
{
    s << quint32(1);
    s << quint32(datas.size());
    for (auto i = datas.constBegin(); i != datas.constEnd(); i++)
    {
        s << i.key() << i.value()->typeName();
        i.value()->writeContent(s);
    }
    s << useIndex;
}

HAdjustCollection::HAdjustCollection(IDataFactory *f) :
    IAdjustCollection(*new HAdjustCollectionPrivate(f))
{
}

HAdjustCollection::HAdjustCollection(HAdjustCollectionPrivate &p) :
    IAdjustCollection(p)
{
}

HAdjustCollection::~HAdjustCollection()
{
}

QString HAdjustCollection::typeName()
{
    return "HAdjustCollection";
}

IDataFactory *HAdjustCollection::dataFactory()
{
    Q_D(HAdjustCollection);
    return d->factory;
}

IFileStream *HAdjustCollection::fileStream()
{
    Q_D(HAdjustCollection);
    return d->fileStream;
}

void HAdjustCollection::setUseIndex(QString value)
{
    Q_D(HAdjustCollection);
    if (d->useIndex == value || !contains(value))
        return;
    d->useIndex = value;
}

QString HAdjustCollection::useIndex()
{
    Q_D(HAdjustCollection);
    return d->useIndex;
}

QVariantMap HAdjustCollection::correct(QVariantMap value)
{
    auto i = item(useIndex());
    return i == nullptr ? QVariantMap() : i->correct(value);
}

HE_DATA_END_NAMESPACE

