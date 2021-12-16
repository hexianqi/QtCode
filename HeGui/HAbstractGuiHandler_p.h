#pragma once

#include "HAbstractGuiHandler.h"

HE_BEGIN_NAMESPACE

class IMainWindow;

class HAbstractGuiHandlerPrivate
{
public:
    HAbstractGuiHandlerPrivate();

public:
    IMainWindow *mainWindow;
};

HE_END_NAMESPACE
