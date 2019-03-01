#include "HSpecCalibrateCollection_p.h"
#include "ISpecCalibrate.h"
#include "IDataFactory.h"
#include "IFileStream.h"
#include <QDataStream>

HE_DATA_BEGIN_NAMESPACE

HSpecCalibrateCollectionPrivate::HSpecCalibrateCollectionPrivate(HSpecCalibrateCollection *q, IDataFactory *f)
    : q_ptr(q)
{
    factory = f;
    fileStream = f->createFileStream("HFileStream");
    fileStream->setMagicNumber(0x00020001);
    fileStream->setFileVersion(0x01010101);
    fileStream->setFileFilter(QObject::tr("Spec calibrate files (*.hcs)"));
    fileStream->setReadContent([=](QDataStream &s) { q_ptr->readContent(s); });
    fileStream->setWriteContent([=](QDataStream &s) { q_ptr->writeContent(s); });
}

HSpecCalibrateCollection::HSpecCalibrateCollection(IDataFactory *f)
    : d_ptr(new HSpecCalibrateCollectionPrivate(this, f))
{
}

HSpecCalibrateCollection::HSpecCalibrateCollection(HSpecCalibrateCollectionPrivate &p)
    : d_ptr(&p)
{
}

HSpecCalibrateCollection::~HSpecCalibrateCollection()
{
}

QString HSpecCalibrateCollection::typeName()
{
    return "HSpecCalibrateCollection";
}

IFileStream *HSpecCalibrateCollection::fileStream()
{
    return d_ptr->fileStream;
}

void HSpecCalibrateCollection::readContent(QDataStream &s)
{
    quint32 version;
    quint32 size;
    QString key, type;

    clear();
    s >> version;
    s >> size;
    for (quint32 i = 0; i < size; i++)
    {
        s >> key >> type;
        auto item = d_ptr->factory->createSpecCalibrate(type);
        item->readContent(s);
        if (s.status() != QDataStream::Ok)
        {
            clear();
            break;
        }
        insert(key, item);
    }
}

void HSpecCalibrateCollection::writeContent(QDataStream &s)
{
    s << quint32(1);
    s << quint32(_datas->size());
    auto i = _datas->constBegin();
    while (i != _datas->constEnd())
    {
        s << i.key() << i.value()->typeName();
        i.value()->writeContent(s);
    }
}

HE_DATA_END_NAMESPACE
