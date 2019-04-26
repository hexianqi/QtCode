#include "HSqlDatabase_p.h"
#include <QtWidgets/QMessageBox>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtCore/QDebug>

HE_SQL_BEGIN_NAMESPACE

HSqlDatabase::HSqlDatabase(QObject *parent) :
    QObject(parent),
    d_ptr(new HSqlDatabasePrivate)
{
}

HSqlDatabase::HSqlDatabase(HSqlDatabasePrivate &p, QObject *parent) :
    QObject(parent),
    d_ptr(&p)
{
}

HSqlDatabase::~HSqlDatabase()
{
    qDebug() << __func__;
}

void HSqlDatabase::initialize(QVariantMap param)
{
    if (param.contains("dbName"))
        openDatabase(param.value("dbName").toString());
}

QString HSqlDatabase::typeName()
{
    return "HSqlDatabase";
}

bool HSqlDatabase::openDatabase(QString dbName)
{
    if (dbName.isEmpty())
        return false;

    if (QSqlDatabase::contains())
    {
        QSqlDatabase::database();
        return true;
    }

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbName);
    if (!db.open())
    {
        QMessageBox::warning(nullptr, tr("打开数据库失败"), db.lastError().text());
        return false;
    }
    return true;
}

void HSqlDatabase::insertTableModel(QString name, ISqlTableModel *model)
{
    d_ptr->tableModels.insert(name, model);
}

ISqlTableModel *HSqlDatabase::tableModel(QString name)
{
    if (d_ptr->tableModels.size() == 0)
        return nullptr;
    if (d_ptr->tableModels.contains(name))
        return d_ptr->tableModels.value(name);
    return d_ptr->tableModels.first();
}

HE_SQL_END_NAMESPACE
