#pragma once

#include "HAbstractPrintSettingDialog.h"

HE_BEGIN_NAMESPACE

class HAbstractPrintSettingDialogPrivate
{
public:
    IPrintTemplate *printTemplate = nullptr;
};

HE_END_NAMESPACE

