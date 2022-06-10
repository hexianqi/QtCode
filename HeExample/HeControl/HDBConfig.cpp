#include "HDBConfig.h"
#include "HeCore/HJsonTree.h"

HE_BEGIN_NAMESPACE

HDBConfig::HDBConfig()
{
    setConigFile(":/sql/dbconfig.json");
}

HDBConfig::~HDBConfig()
{
    delete _json;
}

QString HDBConfig::type() const
{
    return _json->getString("database.type");
}

QString HDBConfig::name() const
{
    return _json->getString("database.name");
}

QString HDBConfig::hostName() const
{
    return _json->getString("database.host");
}

QString HDBConfig::username() const
{
    return _json->getString("database.username");
}

QString HDBConfig::password() const
{
    return _json->getString("database.password");
}

QString HDBConfig::testOnBorrowSql() const
{
    return _json->getString("database.test_on_borrow_sql", "SELECT 1");
}

int HDBConfig::port() const
{
    return _json->getInt("database.port", 0);
}

int HDBConfig::maxWaitTime() const
{
    return _json->getInt("database.max_wait_time", 5000);
}

int HDBConfig::maxConnectionCount() const
{
    return _json->getInt("database.max_connection_count", 5);
}

int HDBConfig::waitInterval() const
{
    return _json->getInt("database.wait_interval", 200);
}

bool HDBConfig::isTestOnBorrow() const
{
    return _json->getBool("database.test_on_borrow", false);
}

bool HDBConfig::isDebug() const
{
    return _json->getBool("database.debug", false);
}

QStringList HDBConfig::sqlFiles() const
{
    return _json->getStringList("database.sql_files");
}

bool HDBConfig::setConigFile(const QString &fileName)
{
    auto json = HJsonTree::fromFile(fileName);
    if (!json->isValid())
        return false;
    _json = json;
    return true;
}

HE_END_NAMESPACE
