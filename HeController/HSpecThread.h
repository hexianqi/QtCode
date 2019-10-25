/***************************************************************************************************
**      2018-06-19  HSpecThread 光谱线程类。
***************************************************************************************************/

#ifndef HSPECTHREAD_H
#define HSPECTHREAD_H

#include "HAbstractThread.h"

HE_CONTROLLER_BEGIN_NAMESPACE

class HSpecThreadPrivate;

class HE_CONTROLLER_EXPORT HSpecThread : public HAbstractThread
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
};

HE_CONTROLLER_END_NAMESPACE

#endif // HSPECTHREAD_H
