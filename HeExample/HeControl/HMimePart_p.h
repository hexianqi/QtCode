#pragma once

#include "HMimePart.h"

HE_BEGIN_NAMESPACE

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

HE_END_NAMESPACE
