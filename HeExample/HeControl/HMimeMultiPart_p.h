#pragma once

#include "HMimeMultiPart.h"
#include "HMimePart_p.h"

HE_BEGIN_NAMESPACE

class HMimeMultiPartPrivate : public HMimePartPrivate
{
public:
    HMimeMultiPartPrivate();

public:
    QList<HMimePart *> parts;
    HMimeMultiPart::MimeType mimeType;
};

HE_END_NAMESPACE
