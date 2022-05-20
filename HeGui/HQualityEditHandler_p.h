#pragma once

#include "HQualityEditHandler.h"
#include "HAbstractConfigHandler_p.h"

HE_BEGIN_NAMESPACE

class HQualityEditHandlerPrivate : public HAbstractConfigHandlerPrivate
{
public:
    QString key = "Spec";
    QString optional;
};

HE_END_NAMESPACE
