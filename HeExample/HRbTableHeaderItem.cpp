#include "HRbTableHeaderItem_p.h"

HRbTableHeaderItemPrivate::HRbTableHeaderItemPrivate(HRbTableHeaderItem *p)
{
    parent = p;
}

HRbTableHeaderItem::HRbTableHeaderItem(HRbTableHeaderItem *parent) :
    d_ptr(new HRbTableHeaderItemPrivate(parent))
{
}

HRbTableHeaderItem::HRbTableHeaderItem(int row, int column, HRbTableHeaderItem *parent) :
    d_ptr(new HRbTableHeaderItemPrivate(parent))
{
    d_ptr->row = row;
    d_ptr->column = column;
}

HRbTableHeaderItem::HRbTableHeaderItem(HRbTableHeaderItemPrivate &p) :
    d_ptr(&p)
{
}

HRbTableHeaderItem::~HRbTableHeaderItem()
{
}

void HRbTableHeaderItem::setData(const QVariant &data, int role)
{
     d_ptr->datas.insert(role, data);
}

QVariant HRbTableHeaderItem::data(int role) const
{
    if (d_ptr->datas.contains(role))
        return d_ptr->datas[role];
    return QVariant();
}

void HRbTableHeaderItem::setText(const QString &text)
{
    d_ptr->datas.insert(Qt::DisplayRole, text);
}

void HRbTableHeaderItem::clear()
{
    for (HRbTableHeaderItem *item : d_ptr->childs)
        delete item;
    d_ptr->childs.clear();
}

int HRbTableHeaderItem::row()
{
    return  d_ptr->row;
}

int HRbTableHeaderItem::column()
{
    return d_ptr->column;
}

HRbTableHeaderItem *HRbTableHeaderItem::parent()
{
    return  d_ptr->parent;
}

HRbTableHeaderItem *HRbTableHeaderItem::insertChild(int row, int column)
{
    auto item = new HRbTableHeaderItem(row, column, this);
    d_ptr->childs.insert(QPair<int, int>(row,column), item);
    return item;
}

const HRbTableHeaderItem *HRbTableHeaderItem::child(int row, int column) const
{
    auto k = QPair<int, int>(row,column);
    if (d_ptr->childs.contains(k))
        return d_ptr->childs[k];
    return nullptr;
}

HRbTableHeaderItem *HRbTableHeaderItem::child(int row, int column)
{
    auto k = QPair<int, int>(row,column);
    if (d_ptr->childs.contains(k))
        return d_ptr->childs[k];
    return nullptr;
}
