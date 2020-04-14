#include "HColorModel.h"


HE_CONTROL_BEGIN_NAMESPACE

QStandardItem *createItem(const QColor &color, const QString &name)
{
    auto item = new QStandardItem;
    item->setText(name);
    item->setData(color, Qt::DecorationRole);
    item->setData(name, Qt::ToolTipRole);
    return item;
}

HColorModel::HColorModel(QObject *parent) :
    QStandardItemModel(parent)
{
    setColumnCount(1);
}

QModelIndex HColorModel::contains(const QColor &color)
{
    auto list = match(index(0, 0), Qt::DecorationRole, color, 1, Qt::MatchExactly);
    return list.isEmpty() ? QModelIndex() : list.first();
}

QModelIndex HColorModel::addColor(const QColor &color, const QString &name)
{
    auto item = createItem(color, name);
    appendRow(item);
    return item->index();
}

QModelIndex HColorModel::insertColor(int index, const QColor &color, const QString &name)
{
    auto item = createItem(color, name);
    insertRow(index, item);
    return item->index();
}

void HColorModel::setStandardColors()
{
    clear();
    for (const auto &name : QColor::colorNames())
        addColor(QColor(name), name);
}

void HColorModel::setColors(const QStringList &value)
{
    clear();
    for (const auto &v : value)
    {
        auto s = v.split(",");
        if (s.size() > 1)
            addColor(QColor(s[0]), s[1]);
    }
}

QStringList HColorModel::colors() const
{
    QStringList list;
    for (int i = 0; i < rowCount();i++)
        list << QString("%1,%2").arg(index(i, 0).data(Qt::DecorationRole).value<QColor>().name(), index(i, 0).data(Qt::ToolTipRole).toString());
    return list;
}

HColorModel *HColorModel::clone(QObject *parent) const
{
    auto model = new HColorModel(parent);
    for (int i = 0; i <  rowCount(); i++)
    {
        model->insertRow(i);
        model->setItemData(model->index(i, 0), itemData(index(i, 0)));
    }
    return model;
}

HE_CONTROL_END_NAMESPACE
