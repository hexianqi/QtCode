#pragma once

#include "HSqlDatabase.h"
#include <QtSql/QSqlDatabase>

HE_BEGIN_NAMESPACE

class HSqlDatabasePrivate
{
public:
    QSqlDatabase db;
    QMap<QString, ISqlTableModel *> tableModels;
};

HE_END_NAMESPACE
