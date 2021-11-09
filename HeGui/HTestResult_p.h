#pragma once

#include "HTestResult.h"
#include "HeData/IXlsxStream.h"

HE_GUI_BEGIN_NAMESPACE

class HTestResultPrivate
{
public:
    HTestResultPrivate();

public:
    void writeContent(Document *);

public:
    IXlsxStream *xlsxStream = nullptr;
    ITestData *testData = nullptr;
    QList<ITestData *> results;
    QStringList syncType;
    QString syncFile;
    int index = 1;
    bool modified = false;
};

HE_GUI_END_NAMESPACE

