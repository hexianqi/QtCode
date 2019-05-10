/***************************************************************************************************
**      2019-04-12  ISqlTableModel 数据库表格模型接口。
***************************************************************************************************/

#ifndef ISQLTABLEMODEL_H
#define ISQLTABLEMODEL_H

#include "HSqlGlobal.h"
#include "HeCore/IInitializeable.h"
#include <QtSql/QSqlTableModel>

HE_CORE_USE_NAMESPACE

HE_SQL_BEGIN_NAMESPACE

class ISqlTableModel : public QSqlTableModel, public IInitializeable
{
    Q_OBJECT

public:
    using QSqlTableModel::QSqlTableModel;

signals:
    void currentRowChanged(int);

public:
    // 设置字段
    virtual void setField(QStringList value) = 0;
    // 字段
    virtual QStringList fields() = 0;
    // 设置表格
    virtual void setTable(QString tableName) = 0;

public:
    // 设置行
    virtual void setCurrentRow(int row) = 0;
};

HE_SQL_END_NAMESPACE

#endif // ISQLTABLEMODEL_H
