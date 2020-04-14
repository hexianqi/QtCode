/***************************************************************************************************
**      2019-12-18  HConnectionPool
***************************************************************************************************/

#ifndef HCONNECTIONPOOL_H
#define HCONNECTIONPOOL_H

#include "HControlGlobal.h"
#include "HeCore/HSingleton2.h"

class QSqlDatabase;

HE_CORE_USE_NAMESPACE

HE_CONTROL_BEGIN_NAMESPACE

class HConnectionPoolPrivate;

class HConnectionPool
{
    H_SINGLETON2(HConnectionPool)

private:
    HConnectionPool();
    ~HConnectionPool();

public:
    QSqlDatabase openConnection();
    void closeConnection(const QSqlDatabase &db);

private:
    QString getConnectionName();
    QSqlDatabase createConnection(const QString &connectionName);

private:
    QScopedPointer<HConnectionPoolPrivate> d_ptr;
};

HE_CONTROL_END_NAMESPACE

#endif // HCONNECTIONPOOL_H
