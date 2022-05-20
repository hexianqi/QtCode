#pragma once

#include "HQualitySelectHandler.h"
#include "HAbstractConfigHandler_p.h"

HE_BEGIN_NAMESPACE

class HQualitySelectHandlerPrivate : public HAbstractConfigHandlerPrivate
{
public:
    QString key = "Spec";
};

HE_END_NAMESPACE
