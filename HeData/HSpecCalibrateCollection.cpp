#include "HSpecCalibrateCollection_p.h"
#include "IDataFactory.h"
#include "ISpecCalibrate.h"
#include "IFileStream.h"
#include <QtCore/QDataStream>

HE_DATA_BEGIN_NAMESPACE

HSpecCalibrateCollectionPrivate::HSpecCalibrateCollectionPrivate(IDataFactory *f)
{
    factory = f;
    fileStream = f->createFileStream("HFileStream");
    fileStream->setMagicNumber(0x00020001);
    fileStream->setFileVersion(0x01010101);
    fileStream->setFileFilter("Spec calibrate files (*.hcs)");
    fileStream->setReadContent([=](QDataStream &s) { readContent(s); });
    fileStream->setWriteContent([=](QDataStream &s) { writeContent(s); });
}

void HSpecCalibrateCollectionPrivate::readContent(QDataStream &s)
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
        auto item = factory->createSpecCalibrate(type);
        item->readContent(s);
        if (s.status() != QDataStream::Ok)
        {
            datas.clear();
            break;
        }
        datas.insert(key, item);
    }
}

void HSpecCalibrateCollectionPrivate::writeContent(QDataStream &s)
{
    s << quint32(1);
    s << quint32(datas.size());
    for (auto i = datas.constBegin(); i != datas.constEnd(); i++)
    {
        s << i.key() << i.value()->typeName();
        i.value()->writeContent(s);
    }
}

HSpecCalibrateCollection::HSpecCalibrateCollection(IDataFactory *f) :
    HCollection<ISpecCalibrate>(*new HSpecCalibrateCollectionPrivate(f))
{
}

HSpecCalibrateCollection::HSpecCalibrateCollection(HSpecCalibrateCollectionPrivate &p) :
    HCollection<ISpecCalibrate>(p)
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
    Q_D(HSpecCalibrateCollection);
    return d->fileStream;
}

HE_DATA_END_NAMESPACE
