#pragma once

#include "HAction.h"

HE_GUI_BEGIN_NAMESPACE

class HActionPrivate
{
public:
    IHandler *handler = nullptr;
};

HE_GUI_END_NAMESPACE
