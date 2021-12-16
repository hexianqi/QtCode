#pragma once

#include "HClearLineEdit.h"
#include "HButtonLineEdit_p.h"

HE_BEGIN_NAMESPACE

class HClearLineEditPrivate : public HButtonLineEditPrivate
{
public:
    bool vis = false;
};

HE_END_NAMESPACE
