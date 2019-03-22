/***************************************************************************************************
**      2018-06-19  HThreadSpec 光谱线程类。
***************************************************************************************************/

#ifndef HTHREADSPEC_H
#define HTHREADSPEC_H

#include "HAbstractThread.h"

HE_CONTROLLER_BEGIN_NAMESPACE

class HThreadSpecPrivate;

class HE_CONTROLLER_EXPORT HThreadSpec : public HAbstractThread
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HThreadSpec)

public:
    explicit HThreadSpec(QObject *parent = nullptr);
    ~HThreadSpec() override;

public:
    QString typeName() override;
    QString threadInfo() override;

protected:
    HThreadSpec(HThreadSpecPrivate &p, QObject *parent = nullptr);

protected:
    HErrorType handleAction(HActionType action) override;
};

HE_CONTROLLER_END_NAMESPACE

#endif // HTHREADSPEC_H
