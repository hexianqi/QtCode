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

void HAdjust::writeContent(QDataStream &s)
{
    s << quint32(1);
    s << quint32(size());
    for (auto i : keys())
    {
        s << i << item(i)->typeName();
        item(i)->writeContent(s);
    }
}

void HAdjust::restoreDefault()
{
    for (auto i : values())
        i->restoreDefault();
}

QVariantMap HAdjust::correct(QVariantMap value)
{
    QVariantMap map;
    for (auto i : keys())
    {
        if (!value.contains(i))
            continue;
        auto v = item(i)->correct(value.value(i));
        if (v.isValid())
        map.insert(i, v);
    }
    return map;
}

HE_DATA_END_NAMESPACE
