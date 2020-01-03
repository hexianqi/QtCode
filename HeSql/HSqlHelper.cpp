#include "HSqlHelper.h"
#include "HSql.h"
#include <QtCore/QStringList>
#include <QtSql/QSqlQuery>

HE_SQL_BEGIN_NAMESPACE

bool HSqlHelper::createTable(QString tableName, QStringList field, QSqlDatabase db)
{
    if (tableName.isEmpty())
        return false;

    QSqlQuery query(db);
    if (db.tables().contains(tableName, Qt::CaseInsensitive))
        query.exec("DROP TABLE " + tableName);
    return query.exec(QString("CREATE TABLE %1 (%2)").arg(tableName).arg(HSql::toCreateStyle(field).join(',')));
}

HE_SQL_END_NAMESPACE
