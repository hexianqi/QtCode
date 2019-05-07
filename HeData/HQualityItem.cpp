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
    d_ptr(new HQualityItemPrivate)
{
    restoreDefault();
}

HQualityItem::HQualityItem(HQualityItemPrivate &p) :
    d_ptr(&p)
{
}

HQualityItem::~HQualityItem()
{
}

void HQualityItem::initialize(QVariantMap param)
{
    if (param.contains("datas"))
        setData(param.value("datas").toMap());
}

QString HQualityItem::typeName()
{
    return "HQualityItem";
}

void HQualityItem::setData(QString name, QVariant value)
{
    d_ptr->datas.insert(name, value);
}

void HQualityItem::setData(QVariantMap value)
{
    for (auto i = value.begin(); i != value.end(); i++)
        setData(i.key(), i.value());
}

QVariant HQualityItem::data(QString name)
{
    return d_ptr->datas.value(name);
}

void HQualityItem::readContent(QDataStream &s)
{
    quint32 version;
    s >> version;
    s >> d_ptr->datas;
}

void HQualityItem::writeContent(QDataStream &s)
{
    s << quint32(1);
    s << d_ptr->datas;
}

void HQualityItem::restoreDefault()
{
    auto f = toFormatInfo(data("[项类型]").toString());
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
    return QStringList() << toCaption(t) << toString(t, p.x()) << toString(t, p.y()) << data("[不足颜色]").value<QColor>().name() << data("[超出颜色]").value<QColor>().name();
}

HE_DATA_END_NAMESPACE
