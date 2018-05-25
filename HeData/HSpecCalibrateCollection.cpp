#include "HSpecCalibrateCollection_p.h"
#include "ISpecCalibrate.h"
#include "IDataFactory.h"
#include <QDataStream>

HE_DATA_BEGIN_NAMESPACE

HSpecCalibrateCollectionPrivate::HSpecCalibrateCollectionPrivate(IDataFactory *f)
    : HAbstractFileStreamPrivate(f)
{
    magicNumber = 0x00020001;
    fileVersion = 0x01010101;
    fileFilter = QObject::tr("Spec calibrate files (*.hcs)");
}

HSpecCalibrateCollection::HSpecCalibrateCollection(HeData::IDataFactory *f)
    : HAbstractFileStream(*new HSpecCalibrateCollectionPrivate(f))
{
}

HSpecCalibrateCollection::HSpecCalibrateCollection(HSpecCalibrateCollectionPrivate &p)
    : HAbstractFileStream(p)
{
}

HSpecCalibrateCollection::~HSpecCalibrateCollection()
{
}

QString HSpecCalibrateCollection::typeName()
{
    return "HSpecCalibrateCollection";
}

void HSpecCalibrateCollection::readContent(QDataStream &s)
{
    Q_D(HSpecCalibrateCollection);

    quint32 version;
    quint32 n;
    QString key, type;

    clear();
    s >> version;
    s >> n;
    for (quint32 i = 0; i < n; i++)
    {
        s >> key >> type;
        auto item = d->factory->createSpecCalibrate(type);
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
    s << typeName();
    s << quint32(1);
    s << quint32(_datas->size());
    auto it = _datas->constEnd();
    auto begin = _datas->constBegin();
    while (it != begin)
    {
        --it;
        s << it.key();
        it.value()->writeContent(s);
    }
}

HE_DATA_END_NAMESPACE
