#include "HItemDelegate_p.h"

HItemDelegate::HItemDelegate(QObject *parent)
    : QItemDelegate(parent), d_ptr(new HItemDelegatePrivate)
{
}

HItemDelegate::HItemDelegate(HItemDelegatePrivate &p, QObject *parent)
    :  QItemDelegate(parent), d_ptr(&p)
{
}

HItemDelegate::~HItemDelegate()
{
}

void HItemDelegate::setOrientation(Qt::Orientation value)
{
    d_ptr->orientation = value;
}

void HItemDelegate::setOrigin(QPoint value)
{
    d_ptr->origin = value;
}

void HItemDelegate::setType(QString value)
{
    d_ptr->typeList = QStringList() << value;
}

void HItemDelegate::setType(QStringList value)
{
    d_ptr->typeList = value;
}

QString HItemDelegate::toType(QModelIndex index) const
{
    auto n = d_ptr->orientation == Qt::Horizontal ? index.column() - d_ptr->origin.x() : index.row() - d_ptr->origin.y();
    n = qMin(n, d_ptr->typeList.size() - 1);
    return d_ptr->typeList[n];
}

bool HItemDelegate::isRedefine(QModelIndex index) const
{
    if (d_ptr->typeList.isEmpty())
        return false;
    if (index.column() < d_ptr->origin.x() || index.row() < d_ptr->origin.y())
        return false;
    return true;
}
