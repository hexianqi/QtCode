#include "HQualityItem_p.h"
#include "HeCore/HCore.h"
#include "HeCore/HDataFormatInfo.h"
#include <QtCore/QPointF>
#include <QtCore/QDataStream>

HE_DATA_BEGIN_NAMESPACE

HQualityItemPrivate::HQualityItemPrivate()
{
    datas.insert("[项类型]", "Undefined");
}

HQualityItem::HQualityItem() :
    IQualityItem(*new HQualityItemPrivate)
{
    restoreDefault();
}

HQualityItem::HQualityItem(HQualityItemPrivate &p) :
    IQualityItem(p)
{
}

QString HQualityItem::typeName()
{
    return "HQualityItem";
}

void HQualityItem::readContent(QDataStream &s)
{
    Q_D(HQualityItem);
    quint32 version;
    s >> version;
    s >> d->datas;
}

void HQualityItem::writeContent(QDataStream &s)
{
    Q_D(HQualityItem);
    s << quint32(1);
    s << d->datas;
}

void HQualityItem::restoreDefault()
{
    auto f = HCore::toFormatInfo(data("[项类型]").toString());
    setData("[有效范围]", QPointF(f->min(), f->max()));
    setData("[不足颜色]", QColor(Qt::red));
    setData("[超出颜色]", QColor(Qt::red));
}

bool HQualityItem::isContains(QVariant value, QColor *color)
{
    bool b;
    auto d = value.toDouble(&b);
    if (!b)
        return false;
    auto range = data("[有效范围]").toPointF();
    if (d < range.x())
    {
        *color = data("[不足颜色]").value<QColor>();
        return false;
    }
    if (d > range.y())
    {
        *color = data("[超出颜色]").value<QColor>();
        return false;
    }
    return true;
}

double HQualityItem::drift(QVariant value)
{
    bool b;
    auto d = value.toDouble(&b);
    if (!b)
        return 0;
    auto range = data("[有效范围]").toPointF();
    return d - (range.x() + range.y()) / 2;
}

QStringList HQualityItem::toStringList()
{
    auto t = data("[项类型]").toString();
    auto p = data("[有效范围]").toPointF();
    return QStringList() << HCore::toString(t, p.x()) << HCore::toString(t, p.y()) << data("[不足颜色]").value<QColor>().name() << data("[超出颜色]").value<QColor>().name();
}

HE_DATA_END_NAMESPACE
