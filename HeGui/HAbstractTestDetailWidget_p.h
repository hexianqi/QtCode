#pragma once

#include "HAbstractTestDetailWidget.h"

class QLineEdit;

HE_BEGIN_NAMESPACE

class ITestData;

class HAbstractTestDetailWidgetPrivate
{
public:
    HAbstractTestDetailWidgetPrivate();

public:
    ITestData *testData;
    QHash<QString, QLineEdit *> lineEdits;
};

HE_END_NAMESPACE
