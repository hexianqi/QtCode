/***************************************************************************************************
**      2020-09-30  HMultStream
***************************************************************************************************/

#pragma once

#include "IMultStream.h"
#include "HAbstractStream.h"

HE_BEGIN_NAMESPACE

class HMultStreamPrivate;

class HMultStream : public HAbstractStream, public virtual IMultStream
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HMultStream)

public:
    explicit HMultStream(QObject *parent = nullptr);
    ~HMultStream() override;

public:
    QString typeName() override;

public:
    QString fileFilter() override;

public:
    bool readFile(QString fileName) override;
    bool writeFile(QString fileName) override;
    void addStream(QString suffix, IStream *, bool focus = true) override;

protected:
    HMultStream(HMultStreamPrivate &p, QObject *parent = nullptr);
};

HE_END_NAMESPACE

