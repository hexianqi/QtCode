/***************************************************************************************************
**      2019-04-12  ISqlTableModel 数据库表格模型接口。
***************************************************************************************************/

#pragma once

#include "HeCore/IInitializeable.h"
#include <QtSql/QSqlTableModel>

HE_BEGIN_NAMESPACE

class ISqlTableModel : public QSqlTableModel, public IInitializeable
{
    Q_OBJECT

public:
    using QSqlTableModel::QSqlTableModel;

signals:
    void currentRowChanged(int);

public:
    // 字段
    virtual QStringList field() = 0;
    // 设置表格
    virtual void setTableField(const QString &tableName, const QStringList &fields) = 0;

public:
    // 是否有效
    virtual bool isValid(int row) = 0;
    // 设置行
    virtual bool setCurrentRow(int row) = 0;
    // 重置行
    virtual void resetCurrentRow(int row) = 0;
    // 当前行
    virtual int currentRow() = 0;
    // 当前记录
    virtual QSqlRecord currentRecord() = 0;
};

HE_END_NAMESPACE
