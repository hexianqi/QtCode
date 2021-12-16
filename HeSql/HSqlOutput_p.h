#pragma once

#include "HSqlOutput.h"

HE_BEGIN_NAMESPACE

class IPrint;
class ITextExport;

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

HE_END_NAMESPACE

