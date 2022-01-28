/***************************************************************************************************
**      2019-04-12  HSqlGlobalInstance 全局进程类。
***************************************************************************************************/

#pragma once

#include "HeCore/HSingleton3.h"
#include <QtCore/QObject>

HE_BEGIN_NAMESPACE

class HSqlGlobalInstance : public QObject
{
    Q_OBJECT
    H_SINGLETON3(HSqlGlobalInstance)

public:
    void initialize();

protected:
    explicit HSqlGlobalInstance(QObject *parent = nullptr);
    ~HSqlGlobalInstance();

protected:
    void initFieldType();
    void initFieldCreateStyle();
    void initFieldGroup();

private:
    bool _initialized = false;
};

HE_END_NAMESPACE
