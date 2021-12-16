#pragma once

#include "HMimeFile.h"
#include "HMimePart_p.h"

HE_BEGIN_NAMESPACE

class HMimeFilePrivate : public HMimePartPrivate
{
public:
    HMimeFilePrivate();

public:
    QString fileName;
};

HE_END_NAMESPACE
