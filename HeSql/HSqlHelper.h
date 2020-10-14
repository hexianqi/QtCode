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
    static bool createTable(const QString &tableName, const QStringList &field, QSqlDatabase db = QSqlDatabase());
    static bool addColumn(const QString &tableName, const QString &field, QSqlDatabase db = QSqlDatabase());
    static bool setVersion(const QString &tableName, int version, QSqlDatabase db = QSqlDatabase());
    static int getVersion(const QString &tableName, QSqlDatabase db = QSqlDatabase());

};

HE_SQL_END_NAMESPACE

#endif // HSQLHELPER_H
