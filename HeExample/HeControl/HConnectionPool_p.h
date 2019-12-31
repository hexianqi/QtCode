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

    int maxConnectionCount = 100;   // 最大连接数
    ulong maxWaitTime = 1000;       // 获取连接最大等待时间
    ulong waitInterval = 200;       // 尝试获取连接时等待间隔时间

    bool check = true;              // 取得连接的时候验证连接是否有效
    QString checkSql = "select 1";  // 测试访问数据库的 SQL
};

HE_CONTROL_END_NAMESPACE

#endif // HCONNECTIONPOOL_P_H
