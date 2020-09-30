#include "HAdjust_p.h"
#include "IDataFactory.h"
#include "IAdjustItem.h"
#include "HStreamHelper.h"
#include "xlsxworksheet.h"
#include "HeCore/HAppContext.h"
#include <QtCore/QPointF>

HE_DATA_BEGIN_NAMESPACE

HAdjustPrivate::HAdjustPrivate()
{
    factory = HAppContext::getContextPointer<IDataFactory>("IDataFactory");
}

HAdjust::HAdjust() :
    IAdjust(*new HAdjustPrivate)
{
}

HAdjust::HAdjust(HAdjustPrivate &p) :
    IAdjust(p)
{
}

QString HAdjust::typeName()
{
    return "HAdjust";
}

void HAdjust::readContent(QDataStream &s)
{
    Q_D(HAdjust);
    quint32 version;

    s >> version;
    HStreamHelper::read<QString, HeData::IAdjustItem>(s, d->datas, [=](QString type) { return d->factory->createAdjustItem(type); });
}

void HAdjust::readContent(Worksheet *p)
{
    Q_D(HAdjust);
    clear();
    auto range = p->dimension();
    auto rowCount = range.rowCount();
    auto colCount = range.columnCount();
    if (rowCount < 2 || colCount < 4)
        return;

    for (int i = 1; i < rowCount; i++)
    {
        auto key = p->read(i, 0).toString();
        if (key.isEmpty())
            break;
        key = QString("[%1]").arg(key);
        auto item = d->factory->createAdjustItem("HAdjustItem");
        item->setData("[项类型]", key);
        item->setData("[调整比率]", p->read(i, 1));
        item->setData("[测试值]", p->read(i, 2));
        item->setData("[标准值]", p->read(i, 3));
        insert(key, item);
    }
}

void HAdjust::writeContent(QDataStream &s)
{
    Q_D(HAdjust);
    s << quint32(1);
    HStreamHelper::write<QString, HeData::IAdjustItem>(s, d->datas);
}

void HAdjust::writeContent(Worksheet *p)
{
    p->write(0, 0, QStringLiteral("项类型"));
    p->write(0, 1, QStringLiteral("调整比率"));
    p->write(0, 2, QStringLiteral("测试值"));
    p->write(0, 3, QStringLiteral("标准值"));
    int row = 1;
    for (auto i : values())
    {
        int column = 0;
        for (auto s : i->toStringList())
        {
            p->write(row, column, s);
            column++;
        }
        row++;
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
    for (const auto &i : keys())
    {
        if (!value.contains(i))
            continue;
        auto v = item(i)->correct(value.value(i));
        if (v.isValid())
            map.insert(i, v);
    }

    if (map.contains("[色坐标x]") && map.contains("[色坐标y]"))
        map.insert("[色坐标]", QPointF(map["[色坐标x]"].toDouble(), map["[色坐标y]"].toDouble()));
    if (map.contains("[色坐标u]") && map.contains("[色坐标v]"))
        map.insert("[色坐标uv]", QPointF(map["[色坐标u]"].toDouble(), map["[色坐标v]"].toDouble()));
    if (map.contains("[色坐标up]") && map.contains("[色坐标vp]"))
        map.insert("[色坐标uvp]", QPointF(map["[色坐标up]"].toDouble(), map["[色坐标vp]"].toDouble()));
    return map;
}

HE_DATA_END_NAMESPACE
