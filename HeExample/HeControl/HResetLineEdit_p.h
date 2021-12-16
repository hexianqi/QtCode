#pragma once

#include "HResetLineEdit.h"
#include "HButtonLineEdit_p.h"

HE_BEGIN_NAMESPACE

class HResetLineEditPrivate : public HButtonLineEditPrivate
{
public:
    QString defaultText;
};

HE_END_NAMESPACE
