#include "HGradeItem_p.h"
#include "HeCore/HCore.h"
#include "HeCore/HDataFormatInfo.h"
#include <QtCore/QDataStream>
#include <QtCore/QPointF>
#include <QtCore/QSet>

HE_DATA_BEGIN_NAMESPACE

HGradeItemPrivate::HGradeItemPrivate()
{
    datas.insert("[项类型]", "Undefined");
    datas.insert("[优先级]", 1);
}

HGradeItem::HGradeItem() :
    HAbstractDataItem(*new HGradeItemPrivate)
{
}

HGradeItem::HGradeItem(HGradeItemPrivate &p) :
    HAbstractDataItem(p)
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

void HGradeItem::setLevels(QVariant value)
{
    Q_D(HGradeItem);
    d->levels = value.value<QList<QPointF>>();
}

QVariant HGradeItem::levels()
{
    Q_D(HGradeItem);
    return QVariant::fromValue(d->levels);
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

QStringList HGradeItem::headers()
{
    auto c = HCore::toCaption(data("[项类型]").toString());
    return QStringList() << c + " Min" << c + " Max";
}

QStringList HGradeItem::types()
{
    auto t = data("[项类型]").toString();
    return QStringList() << t << t;
}

QStringList HGradeItem::level(int i)
{
    Q_D(HGradeItem);
    if (i >= d->levels.size())
        return QStringList() << "" << "";

    QPointF p;
    auto t = data("[项类型]").toString();
    if (i < 0)
    {
        auto f = HCore::toFormatInfo(t);
        p = QPointF(f->min(), f->max());
    }
    else
        p = d->levels[i];
    return QStringList() << HCore::toString(t, p.x()) << HCore::toString(t, p.y());
}

HE_DATA_END_NAMESPACE
