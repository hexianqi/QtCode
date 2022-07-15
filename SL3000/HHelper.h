#pragma once

#include <QtSql/QSqlDatabase>

class QApplication;

class HHelper
{
public:
    static bool initialize();

public:
    static QSqlDatabase createConnectMySql(const QString &connectionName = "mysql");

public:
    static QSqlDatabase mysql;
};

