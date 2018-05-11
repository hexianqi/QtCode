#ifndef HABSTRACTTHREAD_H
#define HABSTRACTTHREAD_H

#include "IThread.h"
#include "HeCore/HErrorType.h"

HE_CORE_USE_NAMESPACE

HE_CONTROLLER_BEGIN_NAMESPACE

class IModel;
class HAbstractThreadPrivate;

class HAbstractThread : public IThread
{
public:
    explicit HAbstractThread(IModel *model, QObject *parent = nullptr);
    ~HAbstractThread();

public:
    virtual void initialize(QVariantMap param) override;

public:
    virtual void stop() override;
    virtual void addAction(HActionType action) override;
    virtual void clearAction() override;

protected:
    HAbstractThread(HAbstractThreadPrivate &p, QObject *parent = nullptr);

protected:
    virtual void run() override;
    virtual bool checkAction(HActionType action);
    virtual HErrorType handleAction(HActionType action) = 0;
    virtual void readSettings();
    virtual void writeSettings();

protected:
    virtual void debugMode();
    virtual void offLineMode();
    virtual void normalMode();
    virtual bool openProtocol();
    virtual void closeProtocol();
    virtual void actionFail(HActionType action, HErrorType error);

protected:
    QScopedPointer<HAbstractThreadPrivate> d_ptr;
};

HE_CONTROLLER_END_NAMESPACE

#endif // HABSTRACTTHREAD_H
