/***************************************************************************************************
**      2019-04-12  HSqlGlobalInstance 全局进程类。
***************************************************************************************************/

#pragma once

#include "HSqlGlobal.h"
#include "HeCore/HSingleton.h"
#include <QtCore/QObject>

HE_CORE_USE_NAMESPACE

HE_SQL_BEGIN_NAMESPACE

class HSqlGlobalInstance : public QObject, public HSingleton<HSqlGlobalInstance>
{
    Q_OBJECT
    H_FRIEND_SINGLETON(HSqlGlobalInstance)

protected:
    explicit HSqlGlobalInstance(QObject *parent = nullptr);
    ~HSqlGlobalInstance();

protected:
    void initFieldType();
    void initFieldCreateStyle();
};

HE_SQL_END_NAMESPACE
