/***************************************************************************************************
**      2019-12-26  HMimeFile
***************************************************************************************************/

#ifndef HMIMEFILE_H
#define HMIMEFILE_H

#include "HMimePart.h"

HE_CONTROL_BEGIN_NAMESPACE

class HMimeFilePrivate;

class HMimeFile : public HMimePart
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HMimeFile)

public:
    explicit HMimeFile(QString fileName, QObject *parent = nullptr);
    ~HMimeFile() override;

public:
    QString fileName() const;

public:
    void setFileName(const QString &value);

protected:
    HMimeFile(HMimeFilePrivate &p, QString fileName, QObject *parent = nullptr);
};

HE_CONTROL_END_NAMESPACE

#endif // HMIMEFILE_H
