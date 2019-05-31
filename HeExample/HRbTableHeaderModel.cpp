#include "HRbTableHeaderModel_p.h"
#include "HRbTableHeaderItem.h"

HRbTableHeaderModelPrivate::HRbTableHeaderModelPrivate(int rows, int columns)
{
    rowCount = rows;
    columnCount = columns;
    root = new HRbTableHeaderItem;
}

HRbTableHeaderModelPrivate::~HRbTableHeaderModelPrivate()
{
    root->clear();
    delete root;
}

HRbTableHeaderModel::HRbTableHeaderModel(int rows, int columns, QObject *parent) :
    QAbstractTableModel(parent),
    d_ptr(new HRbTableHeaderModelPrivate(rows, columns))
{
}

HRbTableHeaderModel::HRbTableHeaderModel(HRbTableHeaderModelPrivate &p, QObject *parent) :
    QAbstractTableModel(parent),
    d_ptr(&p)
{
}

HRbTableHeaderModel::~HRbTableHeaderModel()
{
}

QModelIndex HRbTableHeaderModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    auto parentItem = parent.isValid() ? static_cast<HRbTableHeaderItem *>(parent.internalPointer()) : d_ptr->root;
    auto childItem = parentItem->child(row, column);
    if (childItem == nullptr)
        childItem = parentItem->insertChild(row, column);
    return createIndex(row, column, childItem);
}

int HRbTableHeaderModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return d_ptr->rowCount;
}

int HRbTableHeaderModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return d_ptr->columnCount;
}

QVariant HRbTableHeaderModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= d_ptr->rowCount || index.row() < 0 || index.column() >= d_ptr->columnCount || index.column() < 0)
        return QVariant();

    auto item = static_cast<HRbTableHeaderItem *>(index.internalPointer());
    return item->data(role);
}

bool HRbTableHeaderModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid())
        return false;

    auto item = static_cast<HRbTableHeaderItem *>(index.internalPointer());
    if (role == ColumnSpanRole)
    {
        int column = index.column();
        int span = value.toInt();
        if (span > 0) // span size should be more than 1, else nothing to do
        {
            if (column + span - 1 >= d_ptr->columnCount) // span size should be less than whole columns
                span = d_ptr->columnCount - column;
            item->setData(span, ColumnSpanRole);
        }
    }
    else if (role == RowSpanRole)
    {
        int row = index.row();
        int span = value.toInt();
        if (span > 0) // span size should be more than 1, else nothing to do
        {
            if (row + span - 1 >= d_ptr->rowCount)
                span = d_ptr->rowCount - row;
            item->setData(span, RowSpanRole);
        }
    }
    else
        item->setData(value,role);
    return true;
}
