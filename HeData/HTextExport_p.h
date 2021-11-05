#pragma once

#include "HTextExport.h"

HE_DATA_BEGIN_NAMESPACE

class ITextStream;

class HTextExportPrivate
{
public:
    HTextExportPrivate();

public:
    ITextExportTemplate *textTemplate = nullptr;
    ITextStream *stream = nullptr;
    QString pathName;
    QString fileName;
};

HE_DATA_END_NAMESPACE

