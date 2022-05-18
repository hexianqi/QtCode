#pragma once

#include "HDecoratorDialog.h"

class QGridLayout;

HE_BEGIN_NAMESPACE

class HDecoratorDialogPrivate
{
public:
    IMainWindow *mainWindow = nullptr;
    ITestWidget *widget = nullptr;
    QGridLayout *layout = nullptr;
};

HE_END_NAMESPACE

