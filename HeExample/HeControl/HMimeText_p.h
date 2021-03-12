#pragma once

#include "HMimeText.h"
#include "HMimePart_p.h"

HE_CONTROL_BEGIN_NAMESPACE

class HMimeTextPrivate : public HMimePartPrivate
{
public:
    HMimeTextPrivate();

public:
    QString text;
};

HE_CONTROL_END_NAMESPACE
