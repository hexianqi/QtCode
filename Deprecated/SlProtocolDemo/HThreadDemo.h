/***************************************************************************************************
**      2019-09-12  HThreadDemo
***************************************************************************************************/

#pragma once

#include "HeController/HAbstractThread.h"

HE_CONTROLLER_USE_NAMESPACE

class HThreadDemoPrivate;

class HThreadDemo : public HAbstractThread
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HThreadDemo)

public:
    explicit HThreadDemo(QObject *parent = nullptr);
    ~HThreadDemo() override;

public:
    QString typeName() override;

public:
    QString threadInfo() override;

protected:
    HErrorType handleAction(HActionType action) override;
};
