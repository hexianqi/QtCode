#ifndef HSQLDATABASE_P_H
#define HSQLDATABASE_P_H

#include "HSqlDatabase.h"

HE_SQL_BEGIN_NAMESPACE

class HSqlDatabasePrivate
{
public:
    QMap<QString, ISqlTableModel *> tableModels;
};

HE_SQL_END_NAMESPACE

#endif // HSQLDATABASE_P_H
