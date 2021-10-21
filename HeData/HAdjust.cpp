#include "HAdjust_p.h"
#include "IDataFactory.h"
#include "IAdjustItem.h"
#include "HStreamHelper.h"
#include "QXlsx/xlsxworksheet.h"
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

HAdjust::~HAdjust()
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
    HStreamHelper::read<QString, HeData::IAdjustItem>(s, d->items, [=](QString type) { return d->factory->createAdjustItem(type); });
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

    for (int i = 2; i <= rowCount; i++)
    {
        auto key = p->read(i, 1).toString();
        if (key.isEmpty())
            break;
        key = QString("[%1]").arg(key);
        auto item = d->factory->createAdjustItem("HAdjustItem");
        item->setData("[项类型]", key);
        item->setData("[调整比率]", p->read(i, 2));
        item->setData("[测试值]", p->read(i, 3));
        item->setData("[标准值]", p->read(i, 4));
        insert(key, item);
    }
}

void HAdjust::writeContent(QDataStream &s)
{
    Q_D(HAdjust);
    s << quint32(1);
    HStreamHelper::write<QString, HeData::IAdjustItem>(s, d->items);
}

void HAdjust::writeContent(Worksheet *p)
{
    p->write(1, 1, QStringLiteral("项类型"));
    p->write(1, 2, QStringLiteral("调整比率"));
    p->write(1, 3, QStringLiteral("测试值"));
    p->write(1, 4, QStringLiteral("标准值"));
    int row = 2;
    for (auto i : values())
    {
        int column = 1;
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
    return map;
}

HE_DATA_END_NAMESPACE
