#pragma once

#include "HEmailWidget.h"

HE_BEGIN_NAMESPACE

class HSendEmailThread;

class HEmailWidgetPrivate
{
public:
    HSendEmailThread *thread = nullptr;
};

HE_END_NAMESPACE
