#include "HGradeCollection_p.h"
#include "IDataFactory.h"
#include "IGrade.h"
#include "IFileStream.h"
#include <QtCore/QDataStream>

HE_DATA_BEGIN_NAMESPACE

HGradeCollectionPrivate::HGradeCollectionPrivate(HGradeCollection *q, IDataFactory *f) :
    q_ptr(q)
{
    factory = f;
    fileStream = f->createFileStream("HFileStream");
    fileStream->setMagicNumber(0x00030001);
    fileStream->setFileVersion(0x01010101);
    fileStream->setFileFilter("Grade files (*.hcg)");
    fileStream->setReadContent([=](QDataStream &s) { q_ptr->readContent(s); });
    fileStream->setWriteContent([=](QDataStream &s) { q_ptr->writeContent(s); });
}

HGradeCollection::HGradeCollection(IDataFactory *f) :
    d_ptr(new HGradeCollectionPrivate(this, f))
{
}

HGradeCollection::HGradeCollection(HGradeCollectionPrivate &p) :
    d_ptr(&p)
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
    return d_ptr->fileStream;
}

void HGradeCollection::readContent(QDataStream &s)
{
//    quint32 version;
//    quint32 size;
//    QString key, type;

//    clear();
//    s >> version;
//    s >> size;
//    for (quint32 i = 0; i < size; i++)
//    {
//        s >> key >> type;
//        auto item = d_ptr->factory->createSpecCalibrate(type);
//        item->readContent(s);
//        if (s.status() != QDataStream::Ok)
//        {
//            clear();
//            break;
//        }
//        insert(key, item);
//    }
}

void HGradeCollection::writeContent(QDataStream &s)
{
    s << quint32(1);
    s << quint32(_datas->size());
    auto i = _datas->constBegin();
    while (i != _datas->constEnd())
    {
        s << i.key() << i.value()->typeName();
        i.value()->writeContent(s);
        i++;
    }
}

HE_DATA_END_NAMESPACE
