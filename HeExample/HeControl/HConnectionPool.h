/***************************************************************************************************
**      2019-12-18  HConnectionPool
***************************************************************************************************/

#pragma once

#include "HeCore/HSingleton2.h"

class QSqlDatabase;

HE_BEGIN_NAMESPACE

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

HE_END_NAMESPACE
