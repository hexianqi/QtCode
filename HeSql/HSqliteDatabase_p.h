#pragma once

#include "HSqliteDatabase.h"

HE_BEGIN_NAMESPACE

class HSqliteDatabasePrivate
{
public:
    QSqlDatabase db;
    QMap<QString, ISqlTableModel *> tableModels;
};

HE_END_NAMESPACE
