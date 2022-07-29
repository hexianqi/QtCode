#pragma once

#include "HSqliteDatabase.h"

HE_BEGIN_NAMESPACE

class HSqliteDatabasePrivate
{
public:
    HSqliteDatabasePrivate();

public:
    QString databaseName;
    QSqlDatabase db;
    QMap<QString, ISqlTableModel *> tableModels;
};

HE_END_NAMESPACE
