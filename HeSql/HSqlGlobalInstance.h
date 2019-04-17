/***************************************************************************************************
**      2019-04-12  HSqlGlobalInstance 全局进程类。
***************************************************************************************************/

#ifndef HSQLGLOBALINSTANCE_H
#define HSQLGLOBALINSTANCE_H

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

#endif // HSQLGLOBALINSTANCE_H
