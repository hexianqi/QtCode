#include "HAdjust_p.h"
#include "IDataFactory.h"
#include "IAdjustItem.h"
#include <QtCore/QDataStream>

HE_DATA_BEGIN_NAMESPACE

HAdjust::HAdjust() :
    IAdjust(*new HAdjustPrivate)
{
}

HAdjust::HAdjust(HAdjustPrivate &p) :
    IAdjust(p)
{
}

HAdjust::~HAdjust()
{
}

QString HAdjust::typeName()
{
    return "HAdjust";
}

void HAdjust::readContent(QDataStream &s, IDataFactory *f)
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
        auto item = f->createAdjustItem(type);
        item->readContent(s);
        if (s.status() != QDataStream::Ok)
        {
            clear();
            break;
        }
        insert(key, item);
    }
}

void HAdjust::writeContent(QDataStream &)
{

}

HE_DATA_END_NAMESPACE
