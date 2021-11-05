#pragma once

#include "HSqlOutput.h"

HE_DATA_BEGIN_NAMESPACE
class IPrint;
class ITextExport;
HE_DATA_END_NAMESPACE

HE_SQL_BEGIN_NAMESPACE

class HSqlOutputPrivate
{
public:
    HSqlOutputPrivate();

public:
    ISqlTableModel *model = nullptr;
    ITextExport *textExport = nullptr;
    ITextExportTemplate *textTemplate = nullptr;
    IPrint *print = nullptr;
    IPrintTemplate *printTemplate = nullptr;
};

HE_SQL_END_NAMESPACE

