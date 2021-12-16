#pragma once

#include "HConnectionPool.h"
#include <QtCore/QQueue>

class QWaitCondition;

HE_BEGIN_NAMESPACE

class HConnectionPoolPrivate
{
public:
    HConnectionPoolPrivate();

public:
    QSqlDatabase createConnection(const QString &connectionName);

public:
    QMutex *mutex;
    QWaitCondition *waitConnection;
    QQueue<QString> usedConnectionNames;   // 已使用的数据库连接名
    QQueue<QString> unusedConnectionNames; // 未使用的数据库连接名

    QString databaseType;
    QString databaseName;
    QString hostName;
    QString userName;
    QString password;
    int port;
    bool testOnBorrow = true;
    QString testOnBorrowSql = "select 1";
    int maxConnectionCount = 100;
    int maxWaitTime = 1000;
    int waitInterval = 200;
};

HE_END_NAMESPACE
