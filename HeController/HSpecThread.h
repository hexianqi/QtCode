/***************************************************************************************************
**      2018-06-19  HSpecThread 光谱线程类。
***************************************************************************************************/

#pragma once

#include "HAbstractThread.h"

HE_BEGIN_NAMESPACE

class HSpecThreadPrivate;

class HSpecThread : public HAbstractThread
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HSpecThread)

public:
    explicit HSpecThread(QObject *parent = nullptr);
    ~HSpecThread() override;

public:
    QString typeName() override;

public:
    QString threadInfo() override;

protected:
    HSpecThread(HSpecThreadPrivate &p, QObject *parent = nullptr);

protected:
    virtual void init();
};

HE_END_NAMESPACE
