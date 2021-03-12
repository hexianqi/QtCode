/***************************************************************************************************
**      2019-12-26  HMimeAttachment
***************************************************************************************************/

#pragma once

#include "HMimeFile.h"

HE_CONTROL_BEGIN_NAMESPACE

class HMimeAttachmentPrivate;

class HMimeAttachment : public HMimeFile
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HMimeAttachment)

public:
    explicit HMimeAttachment(const QString &fileName, QObject *parent = nullptr);

public:
    void prepare() override;

protected:
    HMimeAttachment(HMimeAttachmentPrivate &p, const QString &fileName, QObject *parent = nullptr);
};

HE_CONTROL_END_NAMESPACE
