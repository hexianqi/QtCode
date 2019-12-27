#ifndef HMIMEPART_P_H
#define HMIMEPART_P_H

#include "HMimePart.h"

HE_CONTROL_BEGIN_NAMESPACE

class HMimePartPrivate
{
public:
    QString contentId;
    QString contentName;
    QString contentType;
    QString contentCharset;
    QString contentBoundary;
    HMimePart::Encoding contentEncoding = HMimePart::_7Bit;
    QString header;
    QByteArray content;
    QString data;
    bool prepared = false;
};

HE_CONTROL_END_NAMESPACE

#endif // HMIMEPART_P_H
