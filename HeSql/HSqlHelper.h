/***************************************************************************************************
**      2019-04-12  HSqlHelper SQL帮助类。
***************************************************************************************************/

#ifndef HSQLHELPER_H
#define HSQLHELPER_H

#include "HSqlGlobal.h"
#include <QtSql/QSqlDatabase>

HE_SQL_BEGIN_NAMESPACE

class HE_SQL_EXPORT HSqlHelper
{
public:
    static bool createTable(QString tableName, QStringList field, QSqlDatabase db = QSqlDatabase());
};

HE_SQL_END_NAMESPACE

#endif // HSQLHELPER_H
