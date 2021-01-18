#pragma once

#include "HAbstractTestDataEditDialog.h"

HE_GUI_BEGIN_NAMESPACE

class HAbstractTestDataEditDialogPrivate
{
public:
    HAbstractTestDataEditDialogPrivate();

public:
    ITestData *data0 = nullptr;
    ITestData *data1 = nullptr;
};

HE_GUI_END_NAMESPACE

