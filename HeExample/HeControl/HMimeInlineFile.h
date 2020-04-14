/***************************************************************************************************
**      2019-12-26  HMimeInlineFile
***************************************************************************************************/

#ifndef HMIMEINLINEFILE_H
#define HMIMEINLINEFILE_H

#include "HMimeFile.h"

HE_CONTROL_BEGIN_NAMESPACE

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

HE_CONTROL_END_NAMESPACE

#endif // HMIMEINLINEFILE_H
