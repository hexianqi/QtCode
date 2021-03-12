/***************************************************************************************************
**      2019-04-12  HSqlDatabase Sql数据库类。
***************************************************************************************************/

#pragma once

#include "ISqlDatabase.h"

HE_SQL_BEGIN_NAMESPACE

class HSqlDatabasePrivate;

class HSqlDatabase : public QObject, public ISqlDatabase
{
    Q_OBJECT

public:
    explicit HSqlDatabase(QObject *parent = nullptr);
    ~HSqlDatabase() override;

public:
    void initialize(QVariantMap param) override;
    QString typeName() override;

public:
    bool openDatabase(const QString &dbName) override;
    bool contains(const QString &tableName) override;
    void insertTableModel(ISqlTableModel *model) override;
    ISqlTableModel *tableModel(const QString &tableName) override;

protected:
    HSqlDatabase(HSqlDatabasePrivate &p, QObject *parent = nullptr);

protected:
    QScopedPointer<HSqlDatabasePrivate> d_ptr;
};

HE_SQL_END_NAMESPACE
