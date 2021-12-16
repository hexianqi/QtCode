/***************************************************************************************************
**      2019-12-25  HMimeMultiPart
***************************************************************************************************/

#pragma once

#include "HMimePart.h"

HE_BEGIN_NAMESPACE

class HMimeMultiPartPrivate;

class HMimeMultiPart : public HMimePart
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HMimeMultiPart)

public:
    enum MimeType
    {
        Mixed           = 0,            // RFC 2046, section 5.1.3
        Digest          = 1,            // RFC 2046, section 5.1.5
        Alternative     = 2,            // RFC 2046, section 5.1.4
        Related         = 3,            // RFC 2387
        Report          = 4,            // RFC 6522
        Signed          = 5,            // RFC 1847, section 2.1
        Encrypted       = 6             // RFC 1847, section 2.2
    };

public:
    explicit HMimeMultiPart(QObject *parent = nullptr);

public:
    MimeType mimeType() const;
    QList<HMimePart *> parts() const;

public:
    void setMimeType(MimeType type);
    void addPart(HMimePart *);

public:
    void prepare() override;

protected:
    HMimeMultiPart(HMimeMultiPartPrivate &p, QObject *parent = nullptr);
};

HE_END_NAMESPACE
