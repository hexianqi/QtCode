/***************************************************************************************************
**      2019-04-15  HSqlTableModel 数据库表格模型。
***************************************************************************************************/

#ifndef HSQLTABLEMODEL_H
#define HSQLTABLEMODEL_H

#include "ISqlTableModel.h"

HE_SQL_BEGIN_NAMESPACE

class HSqlTableModelPrivate;

class HSqlTableModel : public ISqlTableModel
{
    Q_OBJECT

public:
    explicit HSqlTableModel(QObject *parent = nullptr, QSqlDatabase db = QSqlDatabase());
    ~HSqlTableModel() override;

public:
    void initialize(QVariantMap param) override;
    QString typeName() override;

public:
    QStringList field() override;
    void setTableField(const QString &tableName, const QStringList &fields) override;

public:
    bool isValid(int row) override;
    bool setCurrentRow(int row) override;
    void resetCurrentRow(int index) override;
    int currentRow() override;

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

HE_SQL_END_NAMESPACE

#endif // HSQLTABLEMODEL_H
