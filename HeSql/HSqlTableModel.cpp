#include "HSqlTableModel_p.h"
#include "HSql.h"
#include "HSqlHelper.h"
#include <QtSql/QSqlRecord>
#include <QtCore/QDebug>

HE_SQL_BEGIN_NAMESPACE

HSqlTableModel::HSqlTableModel(QObject *parent, QSqlDatabase db) :
    ISqlTableModel(parent, db),
    d_ptr(new HSqlTableModelPrivate)
{
    init();
}


HSqlTableModel::HSqlTableModel(HSqlTableModelPrivate &p, QObject *parent, QSqlDatabase db) :
    ISqlTableModel(parent, db),
    d_ptr(&p)
{
    init();
}

HSqlTableModel::~HSqlTableModel()
{
    qDebug() << __func__;
}

void HSqlTableModel::initialize(QVariantMap /*param*/)
{

}

QString HSqlTableModel::typeName()
{
    return "HSqlTableModel";
}

void HSqlTableModel::setField(QStringList value)
{
    if (d_ptr->fields == value)
        return;
    d_ptr->fields = value;
}

QStringList HSqlTableModel::field()
{
    return d_ptr->fields;
}

void HSqlTableModel::setTable(const QString &tableName)
{
    auto db = database();
    if (!db.tables().contains(tableName, Qt::CaseInsensitive))
    {
        if (!HSqlHelper::createTable(tableName, d_ptr->fields, db))
            return;
    }
    QSqlTableModel::setTable(tableName);
    setSort(0, Qt::DescendingOrder);
    select();
}

bool HSqlTableModel::isValid(int row)
{
    while (canFetchMore())
        fetchMore();
    return row >= 0 && row < rowCount();
}

bool HSqlTableModel::setCurrentRow(int row)
{
    if (!isValid(row) || d_ptr->currentRow == row)
        return false;
    d_ptr->currentRow = row;
    emit currentRowChanged(row);
    return true;
}

void HSqlTableModel::resetCurrentRow(int index)
{
    d_ptr->currentRow = qMin(index, rowCount() -1);
    emit currentRowChanged(d_ptr->currentRow);
}

int HSqlTableModel::currentRow()
{
    return d_ptr->currentRow;
}

QVariant HSqlTableModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::TextAlignmentRole)
        return Qt::AlignCenter;
    if (role == Qt::DisplayRole || role == Qt::EditRole)
    {
        int n = index.column();
        if (n >= 0 && n < d_ptr->fields.size())
            return HSql::toString(d_ptr->fields[n], QSqlTableModel::data(index, Qt::EditRole));
    }
    return QSqlTableModel::data(index, role);
}

QVariant HSqlTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
    {
        if (section >= 0 && section < d_ptr->fields.size())
            return HSql::toCaptionUnit(d_ptr->fields.at(section));
    }
    return QSqlTableModel::headerData(section, orientation, role);
}

void HSqlTableModel::init()
{
    setEditStrategy(QSqlTableModel::OnManualSubmit);
}

HE_SQL_END_NAMESPACE
