#pragma once

#include "HTestWidget1000I.h"
#include "HeGui/HSpecTestWidget_p.h"

class HTestWidget1000IPrivate : public HTestWidgetPrivate
{
public:
    HTestWidget1000IPrivate();

public:
    IConfigManage *configManage = nullptr;
    ISyncTestResult *testResult = nullptr;
    ISqlHandle *sqlHandle = nullptr;
    IPrint *print = nullptr;
    IPrintTemplate *printTemplate = nullptr;
    ITextExport *textExport = nullptr;
    ITextExportTemplate *textExportTemplate = nullptr;

public:
    QStringList displays;
};

