/***************************************************************************************************
**      2019-12-26  HMimeAttachment
***************************************************************************************************/

#ifndef HMIMEATTACHMENT_H
#define HMIMEATTACHMENT_H

#include "HMimeFile.h"

HE_CONTROL_BEGIN_NAMESPACE

class HMimeAttachmentPrivate;

class HMimeAttachment : public HMimeFile
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HMimeAttachment)

public:
    explicit HMimeAttachment(QString fileName, QObject *parent = nullptr);
    ~HMimeAttachment() override;

public:
    void prepare() override;

protected:
    HMimeAttachment(HMimeAttachmentPrivate &p, QString fileName, QObject *parent = nullptr);
};

HE_CONTROL_END_NAMESPACE

#endif // HMIMEATTACHMENT_H
