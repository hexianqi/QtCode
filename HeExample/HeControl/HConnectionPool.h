/***************************************************************************************************
**      2019-12-18  HConnectionPool
***************************************************************************************************/

#ifndef HCONNECTIONPOOL_H
#define HCONNECTIONPOOL_H

#include "HControlGlobal.h"
#include <QtCore/QVariant>

class QSqlDatabase;

HE_CONTROL_BEGIN_NAMESPACE

class HConnectionPoolPrivate;

class HConnectionPool
{
public:
    static HConnectionPool *instance();
    // 关闭所有的数据库连接
    static void release();
    // 获取数据库连接
    static QSqlDatabase openConnection();
    // 释放数据库连接
    static void closeConnection(QSqlDatabase connection);

public:
    ~HConnectionPool();

public:
    void setDatabaseInfo(QVariantMap param);
    int maxConnectionCount() const;
    int usedCount() const;
    int unusedCount() const;
    int maxWaitTime() const;
    int waitInterval() const;

protected:
    HConnectionPool();
    HConnectionPool(const HConnectionPool&) = delete;
    HConnectionPool &operator=(const HConnectionPool&) = delete;

protected:
    QSqlDatabase createConnection(const QString &connectionName);

protected:
    static QScopedPointer<HConnectionPool> __instance;
    QScopedPointer<HConnectionPoolPrivate> d_ptr;
};

HE_CONTROL_END_NAMESPACE

#endif // HCONNECTIONPOOL_H
