#pragma once

#include "HMimeText.h"
#include "HMimePart_p.h"

HE_BEGIN_NAMESPACE

class HMimeTextPrivate : public HMimePartPrivate
{
public:
    HMimeTextPrivate();

public:
    QString text;
};

HE_END_NAMESPACE
