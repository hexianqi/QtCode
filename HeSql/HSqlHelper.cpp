#include "HSqlHelper.h"
#include "HSql.h"
#include <QtCore/QStringList>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QtCore/QDebug>

HE_SQL_BEGIN_NAMESPACE

bool HSqlHelper::createTable(QString tableName, QStringList field, QSqlDatabase db)
{
    if (tableName.isEmpty())
        return false;

    QSqlQuery query(db);
    if (db.tables().contains(tableName, Qt::CaseInsensitive))
        query.exec("DROP TABLE " + tableName);
    auto sql = QString("CREATE TABLE %1 (%2)").arg(tableName, HSql::toCreateStyle(field).join(','));
    query.exec(sql);
    if (query.lastError().type() != QSqlError::NoError)
    {
        qDebug() << "==> SQL Query: " << query.lastQuery();
        qDebug() << "==> SQL Error: " << query.lastError().text().trimmed();
        return false;
    }
    return true;
}

HE_SQL_END_NAMESPACE
