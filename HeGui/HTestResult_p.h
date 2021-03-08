#pragma once

#include "HTestResult.h"

#include "HeSql/HSqlGlobal.h"

HE_DATA_BEGIN_NAMESPACE
class ITextStream;
HE_DATA_END_NAMESPACE

HE_SQL_BEGIN_NAMESPACE
class ISqlHandle;
class ISqlPrint;
HE_SQL_END_NAMESPACE
HE_SQL_USE_NAMESPACE

HE_GUI_BEGIN_NAMESPACE

class HTestResultPrivate
{
public:
    HTestResultPrivate();

public:
    ISqlHandle *sqlHandle = nullptr;
    ISqlPrint *sqlPrint = nullptr;
    ITextStream *stream = nullptr;
    ITestData *testData = nullptr;
    QList<ITestData *> results;
    QStringList exportTypes;
    QString exportPathName;
    QString exportFileName;
    QString syncFileName;
    int index = 1;
    bool modified = false;
};

HE_GUI_END_NAMESPACE

