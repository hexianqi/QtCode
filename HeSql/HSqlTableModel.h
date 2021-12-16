/***************************************************************************************************
**      2019-04-15  HSqlTableModel 数据库表格模型。
***************************************************************************************************/

#pragma once

#include "ISqlTableModel.h"

HE_BEGIN_NAMESPACE

class HSqlTableModelPrivate;

class HSqlTableModel : public ISqlTableModel
{
    Q_OBJECT

public:
    explicit HSqlTableModel(QObject *parent = nullptr, QSqlDatabase db = QSqlDatabase());
    ~HSqlTableModel() override;

public:
    void initialize(QVariantMap param = QVariantMap()) override;
    QString typeName() override;

public:
    QStringList field() override;
    void setTableField(const QString &tableName, const QStringList &fields) override;

public:
    bool isValid(int row) override;
    bool setCurrentRow(int row) override;
    void resetCurrentRow(int row) override;
    int currentRow() override;
    QSqlRecord currentRecord() override;

public:
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

protected:
    HSqlTableModel(HSqlTableModelPrivate &p, QObject *parent = nullptr, QSqlDatabase db = QSqlDatabase());

protected:
    void init();
    void updateField();

protected:
    QScopedPointer<HSqlTableModelPrivate> d_ptr;
};

HE_END_NAMESPACE
