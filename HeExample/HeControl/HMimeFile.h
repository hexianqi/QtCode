/***************************************************************************************************
**      2019-12-26  HMimeFile
***************************************************************************************************/

#pragma once

#include "HMimePart.h"

HE_BEGIN_NAMESPACE

class HMimeFilePrivate;

class HMimeFile : public HMimePart
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HMimeFile)

public:
    explicit HMimeFile(const QString &fileName, QObject *parent = nullptr);

public:
    QString fileName() const;

public:
    void setFileName(const QString &);

protected:
    HMimeFile(HMimeFilePrivate &p, const QString &fileName, QObject *parent = nullptr);
};

HE_END_NAMESPACE
