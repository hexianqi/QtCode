#include "HConnectionPool_p.h"
#include "HDBConfig.h"
#include <QtCore/QWaitCondition>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QtCore/QDebug>

HE_BEGIN_NAMESPACE

HConnectionPoolPrivate::HConnectionPoolPrivate()
{
    mutex = new QMutex;
    waitConnection = new QWaitCondition;
    auto config = HDBConfig::instance();
    databaseType        = config->type();
    databaseName        = config->name();
    hostName            = config->hostName();
    userName            = config->username();
    password            = config->password();
    port                = config->port();
    testOnBorrow        = config->isTestOnBorrow();
    testOnBorrowSql     = config->testOnBorrowSql();
    maxConnectionCount  = config->maxConnectionCount();
    maxWaitTime         = config->maxWaitTime();
    waitInterval        = config->waitInterval();
    unusedConnectionNames.enqueue(QSqlDatabase::defaultConnection);
}

HConnectionPool::HConnectionPool() :
    d_ptr(new HConnectionPoolPrivate)
{
}

HConnectionPool::~HConnectionPool()
{
    for(const auto &name : d_ptr->usedConnectionNames)
        QSqlDatabase::removeDatabase(name);
    for(const auto &name : d_ptr->unusedConnectionNames)
        QSqlDatabase::removeDatabase(name);
}

QSqlDatabase HConnectionPool::openConnection()
{
    auto connectionName = getConnectionName();
    if (connectionName.isEmpty())
        return QSqlDatabase();

    if (QSqlDatabase::contains(connectionName))
    {
        auto db1 = QSqlDatabase::database(connectionName);
        if (d_ptr->testOnBorrow)
        {
            qDebug() << "Test connection on borrow, execute:" << d_ptr->testOnBorrowSql << ", for " << connectionName;
            QSqlQuery query(d_ptr->testOnBorrowSql, db1);
            if (query.lastError().type() != QSqlError::NoError && !db1.open())
            {
                qDebug() << "Open datatabase error:" << db1.lastError().text();
                return QSqlDatabase();
            }
        }
        d_ptr->usedConnectionNames.enqueue(connectionName);
        return db1;
    }

    auto db = createConnection(connectionName);
    if (db.isOpen())
        d_ptr->usedConnectionNames.enqueue(connectionName);
    return db;
}

void HConnectionPool::closeConnection(QSqlDatabase db)
{
    auto connectionName = db.connectionName();
    if (d_ptr->usedConnectionNames.contains(connectionName))
    {
        QMutexLocker locker(d_ptr->mutex);
        d_ptr->usedConnectionNames.removeOne(connectionName);
        d_ptr->unusedConnectionNames.enqueue(connectionName);
        d_ptr->waitConnection->wakeOne();
    }
    db.close();
}

QString HConnectionPool::getConnectionName()
{
    QMutexLocker locker(d_ptr->mutex);
    auto connectionCount = d_ptr->usedConnectionNames.size() + d_ptr->unusedConnectionNames.size();
    // 如果连接已经用完，等待 waitInterval 毫秒看看是否有可用连接，最长等待 maxWaitTime 毫秒
    for (int i = 0; i < d_ptr->maxWaitTime && connectionCount == d_ptr->maxConnectionCount && d_ptr->unusedConnectionNames.isEmpty(); i += d_ptr->waitInterval)
    {
        d_ptr->waitConnection->wait(d_ptr->mutex, d_ptr->waitInterval);
        connectionCount = d_ptr->usedConnectionNames.size() + d_ptr->unusedConnectionNames.size();
    }
    if (!d_ptr->unusedConnectionNames.isEmpty())
        return d_ptr->unusedConnectionNames.dequeue();
    if (connectionCount < d_ptr->maxConnectionCount)
        return QString("Connection-%1").arg(connectionCount + 1);
    qDebug() << "Cannot create more connections.";
    return QString();
}

QSqlDatabase HConnectionPool::createConnection(const QString &connectionName)
{
    auto db = QSqlDatabase::addDatabase(d_ptr->databaseType, connectionName);
    db.setDatabaseName(d_ptr->databaseName);
    db.setHostName(d_ptr->hostName);
    db.setUserName(d_ptr->userName);
    db.setPassword(d_ptr->password);
    if (d_ptr->port != 0)
        db.setPort(d_ptr->port);
    if (!db.open())
    {
        qDebug() << "Open datatabase error:" << db.lastError().text();
        return QSqlDatabase();
    }
    return db;
}

HE_END_NAMESPACE
