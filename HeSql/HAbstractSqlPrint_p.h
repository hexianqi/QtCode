#ifndef HABSTRACTSQLPRINT_P_H
#define HABSTRACTSQLPRINT_P_H

#include "HAbstractSqlPrint.h"
#include "HeData/HDataGlobal.h"

HE_DATA_BEGIN_NAMESPACE
class ITextStream;
HE_DATA_END_NAMESPACE
HE_DATA_USE_NAMESPACE

HE_SQL_BEGIN_NAMESPACE

class HE_SQL_EXPORT HAbstractSqlPrintPrivate
{
public:
    HAbstractSqlPrintPrivate();

public:
    ISqlTableModel *model = nullptr;
    ITextStream *stream = nullptr;
    QStringList fieldExportExcels;
};

HE_SQL_END_NAMESPACE

#endif // HABSTRACTSQLPRINT_P_H
