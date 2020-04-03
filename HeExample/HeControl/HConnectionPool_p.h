#ifndef HCONNECTIONPOOL_P_H
#define HCONNECTIONPOOL_P_H

#include "HConnectionPool.h"
#include <QtCore/QQueue>

HE_CONTROL_BEGIN_NAMESPACE

class HConnectionPoolPrivate
{
public:
    HConnectionPoolPrivate();

public:
    QSqlDatabase createConnection(const QString &connectionName);

public:
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

HE_CONTROL_END_NAMESPACE

#endif // HCONNECTIONPOOL_P_H
