#ifndef HMIMEMULTIPART_P_H
#define HMIMEMULTIPART_P_H

#include "HMimeMultiPart.h"
#include "HMimePart_p.h"

HE_CONTROL_BEGIN_NAMESPACE

class HMimeMultiPartPrivate : public HMimePartPrivate
{
public:
    HMimeMultiPartPrivate();

public:
    QList<HMimePart *> parts;
    HMimeMultiPart::MimeType mimeType;
};

HE_CONTROL_END_NAMESPACE

#endif // HMIMEMULTIPART_P_H
