#include "HSqlHelper.h"
#include "HSql.h"
#include "ISqlDatabase.h"
#include <QtCore/QStringList>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QtCore/QDebug>

HE_BEGIN_NAMESPACE

bool checkQuery(QSqlQuery *query)
{
    qDebug() << "==> SQL Query: " << query->lastQuery();
    if (query->lastError().type() == QSqlError::NoError)
    {
        qDebug() << "==> SQL Query: OK";
        return true;
    }
    qDebug() << "==> SQL Error: " << query->lastError().text().trimmed();
    return false;
}

bool createVersionManage(QSqlDatabase db)
{
    if (db.tables().contains("VersionManage", Qt::CaseInsensitive))
        return true;
    return HSqlHelper::createTable("VersionManage", QStringList() << "ID" << "TableName" << "Version", db);
}

bool HSqlHelper::createTable(const QString &tableName, const QStringList &fields, QSqlDatabase db)
{
    if (tableName.isEmpty())
        return false;

    if (!db.isValid())
        db = QSqlDatabase::database();

    QSqlQuery query(db);
    if (db.tables().contains(tableName, Qt::CaseInsensitive))
        query.exec("DROP TABLE " + tableName);
    auto sql = QString("CREATE TABLE %1 (%2)").arg(tableName, HSql::toCreateStyle(fields).join(','));
    return query.exec(sql);
}

bool HSqlHelper::truncateTable(const QString &tableName, QSqlDatabase db)
{
    if (tableName.isEmpty())
        return false;

    if (!db.isValid())
        db = QSqlDatabase::database();

    QSqlQuery query(db);
    if (!db.tables().contains(tableName, Qt::CaseInsensitive))
        return false;
    auto sql = QString("TRUNCATE TABLE %1").arg(tableName);
    return query.exec(sql);
}

bool HSqlHelper::addColumn(const QString &tableName, const QString &field, QSqlDatabase db)
{
    if (!db.isValid())
        db = QSqlDatabase::database();

    QSqlQuery query(db);
    auto sql = QString("SELECT * FROM sqlite_master WHERE name = '%1' COLLATE NOCASE AND sql LIKE '%%2%' COLLATE NOCASE").arg(tableName, field);
    query.exec(sql);
    if (query.next())
        return true;

    sql = QString("ALTER TABLE %1 ADD COLUMN %2").arg(tableName, HSql::toCreateStyle(field));
    return query.exec(sql);
}

void HSqlHelper::addColumn(const QString &tableName, const QStringList &fields, QSqlDatabase db)
{
    if (!db.isValid())
        db = QSqlDatabase::database();

    QSqlQuery query(db);
    for (auto field : fields)
    {
        auto sql = QString("SELECT * FROM sqlite_master WHERE name = '%1' COLLATE NOCASE AND sql LIKE '%%2%' COLLATE NOCASE").arg(tableName, field);
        query.exec(sql);
        if (query.next())
            continue;
        sql = QString("ALTER TABLE %1 ADD COLUMN %2").arg(tableName, HSql::toCreateStyle(field));
        query.exec(sql);
    }
}

bool HSqlHelper::setVersion(const QString &tableName, int version, QSqlDatabase db)
{
    if (!db.isValid())
        db = QSqlDatabase::database();

    if (!createVersionManage(db))
        return false;

    QSqlQuery query(db);
    auto sql = QString("SELECT Version FROM VersionManage WHERE TableName = '%1'").arg(tableName);
    query.exec(sql);
    if (query.next())
        sql = QString("UPDATE VersionManage SET Version = %2 WHERE TableName = '%1'").arg(tableName).arg(version);
    else
        sql = QString("INSERT INTO VersionManage (TableName, Version) VALUES ('%1', %2)").arg(tableName).arg(version);
    return query.exec(sql);
}

int HSqlHelper::getVersion(const QString &tableName, QSqlDatabase db)
{
    if (!db.isValid())
        db = QSqlDatabase::database();

    if (!createVersionManage(db))
        return 0;

    QSqlQuery query(db);
    auto sql = QString("SELECT Version FROM VersionManage WHERE TableName = '%1'").arg(tableName);
    query.exec(sql);
    if (query.next())
        return query.value(0).toInt();
    sql = QString("INSERT INTO VersionManage (TableName, Version) VALUES ('%1', %2)").arg(tableName).arg(0x01010101);
    return query.exec(sql) ? 0x01010101 : 0;
}

void HSqlHelper::updateSpecTable(ISqlDatabase *db)
{
    if (db->contains("Spec"))
    {
        auto version = getVersion("Spec");
        // 1.1.1.2 添加列R9
        if (version < 0x01010102)
            addColumn("Spec", "R9");
        // 1.1.1.3 添加列（光合）
        if (version < 0x01010103)
            addColumn("Spec", HSql::membership("|光合信息|"));
        // 1.1.1.4 添加列SDCM
        if (version < 0x01010104)
            addColumn("Spec", "SDCM");
        // 1.1.1.5 添加列TM30
        if (version < 0x01010105)
            addColumn("Spec", QStringList() << "ReflectGraph" << HSql::membership("|TM30信息|"));
        // 1.1.1.6 添加列SDCM
        if (version < 0x01010106)
            addColumn("Spec", "SDCM_Detail");
        // 1.1.1.7 添加列SDCM
        if (version < 0x01010107)
            addColumn("Spec", "LuminousIntensity");
    }
    setVersion("Spec", 0x01010107, db->openConnection());
}

void HSqlHelper::updateAngleTable(ISqlDatabase *db)
{
    setVersion("Angle", 0x01010101, db->openConnection());
}

HE_END_NAMESPACE
