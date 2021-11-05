#pragma once

#include "HTestResult.h"
#include "HeData/IXlsxStream.h"
#include "HeSql/HSqlGlobal.h"

HE_SQL_BEGIN_NAMESPACE
class ISqlHandle;
HE_SQL_END_NAMESPACE
HE_SQL_USE_NAMESPACE

HE_GUI_BEGIN_NAMESPACE

class HTestResultPrivate
{
public:
    HTestResultPrivate();

public:
    void writeContent(Document *);

public:
    ISqlHandle *sqlHandle = nullptr;
    IXlsxStream *xlsxStream = nullptr;
    ITestData *testData = nullptr;
    QList<ITestData *> results;
    QStringList syncType;
    QString syncFile;
    int index = 1;
    bool modified = false;
};

HE_GUI_END_NAMESPACE

