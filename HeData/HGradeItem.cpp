#include "HGradeItem_p.h"
#include <QtCore/QDataStream>
#include <QtCore/QPointF>
#include <QtCore/QSet>

HE_DATA_BEGIN_NAMESPACE

HGradeItem::HGradeItem() :
    HAbstractGradeItem(*new HGradeItemPrivate)
{
}

HGradeItem::~HGradeItem()
{
}

void HGradeItem::initialize(QVariantMap /*param*/)
{

}

QString HGradeItem::typeName()
{
    return "HGradeItem";
}

void HGradeItem::readContent(QDataStream &s)
{
    Q_D(HGradeItem);
    quint32 version;
    s >> version;
    s >> d->datas;
    s >> d->levels;

}

void HGradeItem::writeContent(QDataStream &s)
{
    Q_D(HGradeItem);
    s << quint32(1);
    s << d->datas;
    s << d->levels;
}

QSet<int> HGradeItem::indexOf(QVariant value)
{
    Q_D(HGradeItem);
    QSet<int> r;
    if (!value.canConvert<double>() || count() == 0)
        return r;
    auto v = value.toDouble();
    for (int i = 0; i < d->levels.size(); i++)
    {
        if (v >= d->levels[i].x() && v <= d->levels[i].y())
            r << i;
    }
    return r;
}

int HGradeItem::count()
{
    Q_D(HGradeItem);
    return d->levels.size();
}

HE_DATA_END_NAMESPACE
