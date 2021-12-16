/***************************************************************************************************
**      2019-12-26  HMimeInlineFile
***************************************************************************************************/

#pragma once

#include "HMimeFile.h"

HE_BEGIN_NAMESPACE

class HMimeInlineFilePrivate;

class HMimeInlineFile : public HMimeFile
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HMimeInlineFile)

public:
    explicit HMimeInlineFile(const QString &fileName, QObject *parent = nullptr);

public:
    void prepare() override;

protected:
    HMimeInlineFile(HMimeInlineFilePrivate &p, const QString &fileName, QObject *parent = nullptr);
};

HE_END_NAMESPACE
