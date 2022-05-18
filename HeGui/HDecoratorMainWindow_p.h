#pragma once

#include "HDecoratorMainWindow.h"

HE_BEGIN_NAMESPACE

class HDecoratorMainWindowPrivate
{
public:
    IMainWindow *mainWindow = nullptr;
    ITestWidget *widget = nullptr;
};

HE_END_NAMESPACE

