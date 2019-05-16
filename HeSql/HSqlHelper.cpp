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
    auto text = QString("CREATE TABLE %1 (%2)").arg(tableName).arg(HSql::toCreateStyle(field).join(','));
    query.exec("DROP TABLE " + tableName);
    return query.exec(text);
}

HE_SQL_END_NAMESPACE
