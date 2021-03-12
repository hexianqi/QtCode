#pragma once

#include "HEmailWidget.h"

HE_CONTROL_BEGIN_NAMESPACE

class HSendEmailThread;

class HEmailWidgetPrivate
{
public:
    HSendEmailThread *thread = nullptr;
};

HE_CONTROL_END_NAMESPACE
