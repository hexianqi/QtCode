#pragma once

#include "HSyncTestResult.h"
#include "HeData/IXlsxStream.h"

HE_BEGIN_NAMESPACE

class HSyncTestResultPrivate
{
public:
    HSyncTestResultPrivate();

public:
    void writeContent(Document *);

public:
    IXlsxStream *xlsxStream = nullptr;
    ITestData *testData = nullptr;
    QList<ITestData *> results;
    QStringList syncType;
    QString syncFile;
    bool modified = false;
};

HE_END_NAMESPACE

