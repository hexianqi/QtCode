/***************************************************************************************************
**      2019-04-12  HSqlDatabase Sql数据库类。
***************************************************************************************************/

#pragma once

#include "ISqlDatabase.h"

HE_BEGIN_NAMESPACE

class HSqliteDatabasePrivate;

class HSqliteDatabase : public QObject, public ISqlDatabase
{
    Q_OBJECT

public:
    explicit HSqliteDatabase(QObject *parent = nullptr);
    ~HSqliteDatabase() override;

public:
    void initialize(QVariantMap param = QVariantMap()) override;
    QString typeName() override;

public:
    bool openDatabase(const QString &dbName) override;
    QSqlDatabase getConnection() override;
    bool contains(const QString &tableName) override;
    void insertTableModel(ISqlTableModel *model) override;
    ISqlTableModel *tableModel(const QString &tableName) override;

protected:
    HSqliteDatabase(HSqliteDatabasePrivate &p, QObject *parent = nullptr);

protected:
    QScopedPointer<HSqliteDatabasePrivate> d_ptr;
};

HE_END_NAMESPACE
