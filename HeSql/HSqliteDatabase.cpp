#include "HSqliteDatabase_p.h"
#include "ISqlTableModel.h"
#include "HSqlHelper.h"
#include <QtWidgets/QApplication>
#include <QtWidgets/QMessageBox>
#include <QtSql/QSqlError>

HE_BEGIN_NAMESPACE

HSqliteDatabasePrivate::HSqliteDatabasePrivate()
{
    databaseName = QString("%1.db").arg(QApplication::applicationName());
}

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

void HSqliteDatabase::initialize(QVariantMap /*param*/)
{

}

QString HSqliteDatabase::typeName()
{
    return "HSqliteDatabase";
}

void HSqliteDatabase::setDatabaseName(const QString &name)
{
    if (d_ptr->databaseName == name || name.isEmpty())
        return;
    d_ptr->databaseName = name;
}

QSqlDatabase HSqliteDatabase::openConnection()
{
    if (!d_ptr->db.isValid())
    {
        d_ptr->db = QSqlDatabase::addDatabase("QSQLITE");
        d_ptr->db.setDatabaseName(d_ptr->databaseName);
    }
    if (!d_ptr->db.isOpen())
    {
        if (!d_ptr->db.open())
        {
            QMessageBox::warning(nullptr, tr("打开数据库失败"), d_ptr->db.lastError().text());
            return {};
        }
    }
    return d_ptr->db;
}

void HSqliteDatabase::closeConnection(QSqlDatabase /*db*/)
{
    if (!d_ptr->db.isValid() || !d_ptr->db.isOpen())
        return;
    d_ptr->db.close();
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
