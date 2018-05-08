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
    Q_OBJECT

public:
    explicit HAbstractThread(IModel *model, QObject *parent = nullptr);
    ~HAbstractThread();

signals:
    void startFailed(HErrorType err);
    void startFinished();
    void stopFinished();
    void actionFailed(HActionType action, HErrorType err);
    void actionFinished(HActionType action);


    void protocolFailed(HErrorType err);
    void protocolOpened();
    void protocolClosed();
    void actionDealFailed(HActionType action, HErrorType err);
    void actionDealFinished(HActionType action);

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
    virtual HErrorType openProtocol();
    virtual void closeProtocol();


protected:
    QScopedPointer<HAbstractThreadPrivate> d_ptr;
};

HE_CONTROLLER_END_NAMESPACE

#endif // HABSTRACTTHREAD_H
