/***************************************************************************************************
**      2019-04-12  HSqlHelper SQL帮助类。
***************************************************************************************************/

#pragma once

#include "HSqlGlobal.h"
#include <QtSql/QSqlDatabase>

HE_SQL_BEGIN_NAMESPACE

class HE_SQL_EXPORT HSqlHelper
{
public:
    static bool createTable(const QString &tableName, const QStringList &fields, QSqlDatabase db = QSqlDatabase());
    static bool addColumn(const QString &tableName, const QString &field, QSqlDatabase db = QSqlDatabase());
    static void addColumn(const QString &tableName, const QStringList &fields, QSqlDatabase db = QSqlDatabase());
    static bool setVersion(const QString &tableName, int version, QSqlDatabase db = QSqlDatabase());
    static int getVersion(const QString &tableName, QSqlDatabase db = QSqlDatabase());
};

HE_SQL_END_NAMESPACE
