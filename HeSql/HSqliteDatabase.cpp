#include "HSqliteDatabase_p.h"
#include "ISqlTableModel.h"
#include "HSqlHelper.h"
#include <QtWidgets/QMessageBox>
#include <QtSql/QSqlError>

HE_BEGIN_NAMESPACE

HSqliteDatabase::HSqliteDatabase(QObject *parent) :
    QObject(parent),
    d_ptr(new HSqliteDatabasePrivate)
{
}

HSqliteDatabase::HSqliteDatabase(HSqliteDatabasePrivate &p, QObject *parent) :
    QObject(parent),
    d_ptr(&p)
{
}

HSqliteDatabase::~HSqliteDatabase() = default;

void HSqliteDatabase::initialize(QVariantMap param)
{
    if (param.contains("dbName"))
        openDatabase(param.value("dbName").toString());
}

QString HSqliteDatabase::typeName()
{
    return "HSqlDatabase";
}

bool HSqliteDatabase::openDatabase(const QString &dbName)
{
    if (dbName.isEmpty())
        return false;

    if (QSqlDatabase::contains())
    {
        QSqlDatabase::database();
        return true;
    }

    d_ptr->db = QSqlDatabase::addDatabase("QSQLITE");
    d_ptr->db.setDatabaseName(dbName);
    if (!d_ptr->db.open())
    {
        QMessageBox::warning(nullptr, tr("打开数据库失败"), d_ptr->db.lastError().text());
        return false;
    }
    return true;
}

QSqlDatabase HSqliteDatabase::getConnection()
{
    Q_ASSERT_X(d_ptr->db.isValid() && d_ptr->db.isOpen(), "HSqliteDatabase", "database is invalid or closed.");
    return d_ptr->db;
}

bool HSqliteDatabase::contains(const QString &tableName)
{
    Q_ASSERT_X(d_ptr->db.isValid() && d_ptr->db.isOpen(), "HSqliteDatabase", "database is invalid or closed.");
    return d_ptr->db.tables().contains(tableName);
}

void HSqliteDatabase::insertTableModel(ISqlTableModel *model)
{
    d_ptr->tableModels.insert(model->tableName(), model);
}

ISqlTableModel *HSqliteDatabase::tableModel(const QString &tableName)
{
    if (d_ptr->tableModels.isEmpty())
        return nullptr;
    if (d_ptr->tableModels.contains(tableName))
        return d_ptr->tableModels.value(tableName);
    return d_ptr->tableModels.first();
}

HE_END_NAMESPACE
