#pragma once

#include "HPrintSettingHandler.h"
#include "HAbstractGuiHandler_p.h"

HE_BEGIN_NAMESPACE

class IGuiFactory;

class HPrintSettingHandlerPrivate : public HAbstractGuiHandlerPrivate
{
public:
    HPrintSettingHandlerPrivate();

public:
    IGuiFactory *guiFactory = nullptr;
    QString printTemplate = "ISpecPrintTemplate";
    QString printSettingDialog = "HSpecPrintSettingDialog";
};

HE_END_NAMESPACE

