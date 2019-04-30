#include "HAbstractGrade_p.h"
#include "IDataFactory.h"
#include "IGradeItem.h"
#include <QtCore/QDataStream>

HE_DATA_BEGIN_NAMESPACE

HAbstractGrade::HAbstractGrade() :
    IGrade(*new HAbstractGradePrivate)
{
}

HAbstractGrade::HAbstractGrade(HAbstractGradePrivate &p) :
    IGrade(p)
{
}

HAbstractGrade::~HAbstractGrade()
{
}

void HAbstractGrade::readContent(QDataStream &s, IDataFactory *f)
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
        auto item = f->createGradeItem(type);
        item->readContent(s);
        if (s.status() != QDataStream::Ok)
        {
            clear();
            break;
        }
        insert(key, item);
    }
}

void HAbstractGrade::writeContent(QDataStream &s)
{
    s << quint32(1);
    s << quint32(size());
    for (auto i : keys())
    {
        s << i << item(i)->typeName();
        item(i)->writeContent(s);
    }
}

QVariant HAbstractGrade::levels(QString type)
{
    return contains(type) ? value(type)->levels() : QVariant();
}

HE_DATA_END_NAMESPACE
