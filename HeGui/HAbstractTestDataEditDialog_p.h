#pragma once

#include "HAbstractTestDataEditDialog.h"

HE_BEGIN_NAMESPACE

class HAbstractTestDataEditDialogPrivate
{
public:
    HAbstractTestDataEditDialogPrivate();

public:
    ITestData *data();

public:
    ITestData *data0 = nullptr;
    ITestData *data1 = nullptr;
};

HE_END_NAMESPACE

