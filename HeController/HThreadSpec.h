#ifndef HTHREADSPEC_H
#define HTHREADSPEC_H

#include "HAbstractThread.h"

HE_CONTROLLER_BEGIN_NAMESPACE

class HThreadSpecPrivate;

class HThreadSpec : public HAbstractThread
{
    Q_DECLARE_PRIVATE(HThreadSpec)

public:
    explicit HThreadSpec(IModel *model, QObject *parent = nullptr);
    ~HThreadSpec();

public:
    virtual QString threadInfo() override;

protected:
    HThreadSpec(HThreadSpecPrivate &p, QObject *parent = nullptr);

protected:
    virtual HErrorType handleAction(HActionType action) override;
};

HE_CONTROLLER_END_NAMESPACE

#endif // HTHREADSPEC_H
