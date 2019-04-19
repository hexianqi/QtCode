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
}


HSqlTableModel::HSqlTableModel(HSqlTableModelPrivate &p, QObject *parent, QSqlDatabase db) :
    ISqlTableModel(parent, db),
    d_ptr(&p)
{
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

void HSqlTableModel::setTable(QString tableName)
{
    auto db = database();
    if (!db.tables().contains(tableName))
    {
        if (!HSqlHelper::createTable(tableName, d_ptr->fields, db))
            return;
    }
    QSqlTableModel::setTable(tableName);
    setSort(0, Qt::AscendingOrder);
    select();
}

bool HSqlTableModel::addRecord(QVariantMap value)
{
//    QVariant v;
//    auto r = record();
//    for (auto f : d_ptr->fields)
//    {
//        if (f == "ID")
//            continue;
//        v = value.value(f);
//        r.setValue(f, v);
//    }
    return false;
}

QStringList HSqlTableModel::fields()
{
    return d_ptr->fields;
}

QVariant HSqlTableModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::TextAlignmentRole)
        return int(Qt::AlignHCenter | Qt::AlignVCenter);
    if (role == Qt::DisplayRole || role == Qt::EditRole)
    {
        int n;
        n = index.column();
        if (n >= 0 && n < d_ptr->fields.size())
            return toString(d_ptr->fields[n], QSqlTableModel::data(index, Qt::EditRole));
    }
    return QSqlTableModel::data(index, role);
}

QVariant HSqlTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
    {
        if (section >= 0 && section < d_ptr->fields.size())
            return toCaptionUnit(d_ptr->fields[section]);
    }
    return QSqlTableModel::headerData(section, orientation, role);
}

HE_SQL_END_NAMESPACE
