#include "HConnectionPool_p.h"
#include <QtCore/QMutexLocker>
#include <QtCore/QWaitCondition>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QtCore/QDebug>

HE_CONTROL_BEGIN_NAMESPACE

static QMutex __mutex;
static QWaitCondition __waitConnection;

QScopedPointer<HConnectionPool> HConnectionPool::__instance;

HConnectionPool::HConnectionPool() :
    d_ptr(new HConnectionPoolPrivate)
{
    d_ptr->databaseType = "QMYSQL";
    d_ptr->databaseName = "quick";
    d_ptr->hostName     = "localhost";
    d_ptr->userName     = "root";
    d_ptr->password     = "";
}

HConnectionPool::~HConnectionPool()
{
    for(auto name : d_ptr->usedConnectionNames)
        QSqlDatabase::removeDatabase(name);
    for(auto name : d_ptr->unusedConnectionNames)
        QSqlDatabase::removeDatabase(name);
}

void HConnectionPool::setDatabaseInfo(QVariantMap param)
{
    if (param.contains("hostName"))
        d_ptr->hostName = param.value("hostName").toString();
    if (param.contains("databaseName"))
        d_ptr->databaseName = param.value("databaseName").toString();
    if (param.contains("userName"))
        d_ptr->userName = param.value("userName").toString();
    if (param.contains("password"))
        d_ptr->password = param.value("password").toString();
    if (param.contains("databaseType"))
        d_ptr->databaseType = param.value("databaseType").toString();
}

HConnectionPool *HConnectionPool::instance()
{
    if (__instance.isNull())
    {
        QMutexLocker locker(&__mutex);
        if (__instance.isNull())
            __instance.reset(new HConnectionPool);
    }
    return __instance.data();
}

int HConnectionPool::maxConnectionCount() const
{
    return d_ptr->maxConnectionCount;
}

int HConnectionPool::usedCount() const
{
    return d_ptr->usedConnectionNames.size();
}

int HConnectionPool::unusedCount() const
{
    return d_ptr->unusedConnectionNames.size();
}

int HConnectionPool::maxWaitTime() const
{
    return d_ptr->maxWaitTime;
}

int HConnectionPool::waitInterval() const
{
    return d_ptr->waitInterval;
}

void HConnectionPool::release()
{
    QMutexLocker locker(&__mutex);
    __instance.reset();
}

QSqlDatabase HConnectionPool::openConnection()
{
    auto pool = instance();

    QString connectionName;
    QMutexLocker locker(&__mutex);

    // 已创建连接数
    auto connectionCount = pool->usedCount() + pool->unusedCount();

    // 如果连接已经用完，等待 waitInterval 毫秒看看是否有可用连接，最长等待 maxWaitTime 毫秒
    for (int i = 0; i < pool->maxWaitTime() && pool->unusedCount() == 0 && connectionCount == pool->maxConnectionCount(); i += pool->waitInterval())
    {
        __waitConnection.wait(&__mutex, pool->waitInterval());
        connectionCount = pool->usedCount() + pool->unusedCount();
    }

    if (pool->unusedCount() > 0)
    {
        // 有已经回收的连接，复用它们
        connectionName = pool->d_ptr->unusedConnectionNames.dequeue();
    }
    else if (connectionCount < pool->maxConnectionCount())
    {
        // 没有已经回收的连接，但是没有达到最大连接数，则创建新的连接
        connectionName = QString("Connection-%1").arg(connectionCount + 1);
    }
    else
    {
        // 已经达到最大连接数
        qDebug() << "Cannot create more connections.";
        return QSqlDatabase();
    }

    // 创建连接
    auto db = pool->createConnection(connectionName);

    // 有效的连接才放入 usedConnectionNames
    if (db.isOpen())
        pool->d_ptr->usedConnectionNames.enqueue(connectionName);
    return db;
}

void HConnectionPool::closeConnection(QSqlDatabase connection)
{
    auto pool = instance();
    auto connectionName = connection.connectionName();
    if (pool->d_ptr->usedConnectionNames.contains(connectionName))
    {
        QMutexLocker locker(&__mutex);
        pool->d_ptr->usedConnectionNames.removeOne(connectionName);
        pool->d_ptr->unusedConnectionNames.enqueue(connectionName);
        __waitConnection.wakeOne();
    }
}

QSqlDatabase HConnectionPool::createConnection(const QString &connectionName)
{
    // 连接已经创建过了，复用它，而不是重新创建
    if (QSqlDatabase::contains(connectionName))
    {
        auto db1 = QSqlDatabase::database(connectionName);
        if (d_ptr->check)
        {
            // 返回连接前访问数据库，如果连接断开，重新建立连接
            qDebug() << "Test connection on borrow, execute:" << d_ptr->checkSql << ", for" << connectionName;
            QSqlQuery query(d_ptr->checkSql, db1);
            if (query.lastError().type() != QSqlError::NoError && !db1.open())
            {
                qDebug() << "Open datatabase error:" << db1.lastError().text();
                return QSqlDatabase();
            }
        }
        return db1;
    }

    // 创建一个新的连接
    auto db = QSqlDatabase::addDatabase(d_ptr->databaseType, connectionName);
    db.setDatabaseName(d_ptr->databaseName);
    db.setHostName(d_ptr->hostName);
    db.setUserName(d_ptr->userName);
    db.setPassword(d_ptr->password);

    if (!db.open())
    {
        qDebug() << "Open datatabase error:" << db.lastError().text();
        return QSqlDatabase();
    }
    return db;
}

HE_CONTROL_END_NAMESPACE
