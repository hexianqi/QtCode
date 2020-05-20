#include "HStyledItemDelegate_p.h"

HStyledItemDelegate::HStyledItemDelegate(QObject *parent) :
    QStyledItemDelegate(parent),
    d_ptr(new HStyledItemDelegatePrivate)
{
}

HStyledItemDelegate::HStyledItemDelegate(HStyledItemDelegatePrivate &p, QObject *parent) :
    QStyledItemDelegate(parent),
    d_ptr(&p)
{
}

HStyledItemDelegate::~HStyledItemDelegate() = default;

void HStyledItemDelegate::setOrientation(Qt::Orientation value)
{
    d_ptr->orientation = value;
}

void HStyledItemDelegate::setOrigin(QPoint value)
{
    d_ptr->origin = value;
}

void HStyledItemDelegate::setType(const QString &value)
{
    d_ptr->typeList = QStringList() << value;
}

void HStyledItemDelegate::setType(const QStringList &value)
{
    d_ptr->typeList = value;
}

QString HStyledItemDelegate::toType(QModelIndex index) const
{
    auto n = d_ptr->orientation == Qt::Horizontal ? index.column() - d_ptr->origin.x() : index.row() - d_ptr->origin.y();
    n = qMin(n, d_ptr->typeList.size() - 1);
    return d_ptr->typeList.at(n);
}

bool HStyledItemDelegate::isRedefine(QModelIndex index) const
{
    if (d_ptr->typeList.isEmpty())
        return false;
    if (index.column() < d_ptr->origin.x() || index.row() < d_ptr->origin.y())
        return false;
    return true;
}
