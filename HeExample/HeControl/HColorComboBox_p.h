#pragma once

#include "HColorComboBox.h"

HE_BEGIN_NAMESPACE

class HColorModel;

class HColorComboBoxPrivate
{
public:
    HColorModel *model = nullptr;
    bool colorDialogEnabled = false;
};

HE_END_NAMESPACE
