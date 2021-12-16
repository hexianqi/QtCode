/***************************************************************************************************
**      2019-04-12  HSqlGlobalInstance 全局进程类。
***************************************************************************************************/

#pragma once

#include "HeCore/HSingleton.h"
#include <QtCore/QObject>

HE_BEGIN_NAMESPACE

class HSqlGlobalInstance : public QObject, public HSingleton<HSqlGlobalInstance>
{
    Q_OBJECT
    H_FRIEND_SINGLETON(HSqlGlobalInstance)

public:
    void init();

protected:
    explicit HSqlGlobalInstance(QObject *parent = nullptr);
    ~HSqlGlobalInstance();

protected:
    void initFieldType();
    void initFieldCreateStyle();
};

HE_END_NAMESPACE
