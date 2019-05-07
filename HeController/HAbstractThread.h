/***************************************************************************************************
**      2018-06-19  HAbstractThread 抽象线程类。
***************************************************************************************************/

#ifndef HABSTRACTTHREAD_H
#define HABSTRACTTHREAD_H

#include "IThread.h"
#include "HeCore/HErrorType.h"

HE_CONTROLLER_BEGIN_NAMESPACE

class HAbstractThreadPrivate;

class HAbstractThread : public IThread
{
    Q_OBJECT

public:
    explicit HAbstractThread(QObject *parent = nullptr);
    ~HAbstractThread() override;

public:
    void initialize(QVariantMap param) override;

public:
    void stop() override;
    void addAction(HActionType action) override;
    void clearAction() override;

protected:
    HAbstractThread(HAbstractThreadPrivate &p, QObject *parent = nullptr);

protected:
    virtual void run() override;
    virtual bool checkAction(HActionType action);
    virtual HErrorType handleAction(HActionType action) = 0;

protected:
    virtual void debugMode();
    virtual void offlineMode();
    virtual void normalMode();

protected:
    virtual bool openProtocol();
    virtual void closeProtocol();
    virtual void actionFail(HActionType action, HErrorType error);

protected:
    QScopedPointer<HAbstractThreadPrivate> d_ptr;

private:
    void readSettings();
    void writeSettings();
};

HE_CONTROLLER_END_NAMESPACE

#endif // HABSTRACTTHREAD_H
