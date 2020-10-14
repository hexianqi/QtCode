#ifndef HSQLDATABASE_P_H
#define HSQLDATABASE_P_H

#include "HSqlDatabase.h"
#include <QtSql/QSqlDatabase>

HE_SQL_BEGIN_NAMESPACE

class HSqlDatabasePrivate
{
public:
    QSqlDatabase db;
    QMap<QString, ISqlTableModel *> tableModels;
};

HE_SQL_END_NAMESPACE

#endif // HSQLDATABASE_P_H
