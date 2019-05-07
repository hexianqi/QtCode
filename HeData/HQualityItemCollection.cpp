#include "HQualityItemCollection_p.h"
#include "IDataFactory.h"
#include "IQualityItem.h"
#include <QtCore/QDataStream>
#include <QtGui/QColor>

HE_DATA_BEGIN_NAMESPACE

HQualityItemCollection::HQualityItemCollection() :
    IQualityItemCollection(*new HQualityItemCollectionPrivate)
{
}

HQualityItemCollection::HQualityItemCollection(HQualityItemCollectionPrivate &p) :
    IQualityItemCollection(p)
{
}

HQualityItemCollection::~HQualityItemCollection()
{
}

QString HQualityItemCollection::typeName()
{
    return "HQualityItemCollection";
}

void HQualityItemCollection::readContent(QDataStream &s, IDataFactory *f)
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
        auto item = f->createQualityItem(type);
        item->readContent(s);
        if (s.status() != QDataStream::Ok)
        {
            clear();
            break;
        }
        insert(key, item);
    }
}

void HQualityItemCollection::writeContent(QDataStream &s)
{
    s << quint32(1);
    s << quint32(size());
    for (auto i : keys())
    {
        s << i << item(i)->typeName();
        item(i)->writeContent(s);
    }
}

int HQualityItemCollection::check(QVariantMap value, QVariantMap *color)
{
    for (auto i : keys())
    {
        if (!value.contains(i))
            return -1;
    }
    for (auto i : keys())
    {
        QColor c;
        if (!item(i)->isContains(value.value(i), &c))
            color->insert(i, c);
    }
    return color->size() > 0 ? 1: 0;
}

double HQualityItemCollection::drift(QString type, QVariant value)
{
    if (!contains(type))
        return 0;
    return item(type)->drift(value);
}

HE_DATA_END_NAMESPACE
