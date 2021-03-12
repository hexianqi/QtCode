#pragma once

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
    bool ribbon = true;
    bool paintTitle = true;
    bool paintLogo = true;

public:
    ISqlTableModel *model = nullptr;
    ITextStream *stream = nullptr;
    QStringList fieldExportExcels;
};

HE_SQL_END_NAMESPACE
