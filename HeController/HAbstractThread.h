/***************************************************************************************************
**      2018-06-19  HAbstractThread 抽象线程类。
***************************************************************************************************/

#pragma once

#include "IThread.h"

HE_BEGIN_NAMESPACE

class HAbstractThreadPrivate;

class HE_CONTROLLER_EXPORT HAbstractThread : public IThread
{
    Q_OBJECT

public:
    explicit HAbstractThread(QObject *parent = nullptr);
    ~HAbstractThread() override;

public:
    void initialize(QVariantMap param = QVariantMap()) override;

public:
    void stop() final;
    void addAction(HActionType action) override;
    void clearAction() override;

protected:
    HAbstractThread(HAbstractThreadPrivate &p, QObject *parent = nullptr);

protected:
    void run() override;
    virtual bool checkAction(HActionType action);
    virtual bool handleAction(HActionType action);
    virtual bool isSupport(HActionType action);

protected:
    virtual bool openProtocol();
    virtual void closeProtocol();

protected:
    QScopedPointer<HAbstractThreadPrivate> d_ptr;

private:
    void readSettings();
    void writeSettings();
};

HE_END_NAMESPACE
