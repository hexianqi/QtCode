#ifndef HSQLTABLEMODEL_P_H
#define HSQLTABLEMODEL_P_H

#include "HSqlTableModel.h"

HE_SQL_BEGIN_NAMESPACE

class HSqlTableModelPrivate
{
public:
    QStringList fields;
    int currentRow = -1;
};

HE_SQL_END_NAMESPACE

#endif // HSQLTABLEMODEL_P_H
