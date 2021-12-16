#pragma once

#include "HAction.h"

HE_BEGIN_NAMESPACE

class HActionPrivate
{
public:
    IHandler *handler = nullptr;
};

HE_END_NAMESPACE
