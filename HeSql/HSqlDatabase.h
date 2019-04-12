/***************************************************************************************************
**      2019-04-12  HSqlDatabase Sql数据库类。
***************************************************************************************************/

#ifndef HSQLDATABASE_H
#define HSQLDATABASE_H

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
    bool openDatabase(QString dbName) override;
    void insertTableModel(QString name, ISqlTableModel *model) override;
    ISqlTableModel *tableModel(QString name) override;

protected:
    HSqlDatabase(HSqlDatabasePrivate &p, QObject *parent = nullptr);

protected:
    QScopedPointer<HSqlDatabasePrivate> d_ptr;
};

HE_SQL_END_NAMESPACE

#endif // HSQLDATABASE_H
