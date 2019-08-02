#include "HColorModel.h"

HE_CONTROL_BEGIN_NAMESPACE

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
    auto item = new QStandardItem;
    item->setText(name);
    item->setData(color, Qt::DecorationRole);
    item->setData(name, Qt::ToolTipRole);
    appendRow(item);
    return item->index();
}

QModelIndex HColorModel::insertColor(int index, const QColor &color, const QString &name)
{
    auto *item = new QStandardItem;
    item->setText(name);
    item->setData(color, Qt::DecorationRole);
    item->setData(name, Qt::ToolTipRole);
    insertRow(index, item);
    return item->index();
}

void HColorModel::setStandardColors()
{
    clear();
    for (auto name : QColor::colorNames())
        addColor(QColor(name), name);
}

QStringList HColorModel::colors() const
{
    QStringList list;
    for (int i = 0; i < rowCount();i++)
        list << QString("%1,%2").arg(qvariant_cast<QColor>(index(i, 0).data(Qt::DecorationRole)).name()).arg(index(i, 0).data(Qt::ToolTipRole).toString());
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
