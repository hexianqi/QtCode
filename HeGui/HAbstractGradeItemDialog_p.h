#pragma once

#include "HAbstractGradeItemDialog.h"

HE_BEGIN_NAMESPACE

class HAbstractGradeItemDialogPrivate
{
public:
    IGradeItem *data = nullptr;
    QString type;
    bool averageMode = false;
};

HE_END_NAMESPACE
