/***************************************************************************************************
**      2019-05-31  HRbTableHeaderModel 多标题模型
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include <QtCore/QAbstractTableModel>

HE_BEGIN_NAMESPACE

class HRbTableHeaderModelPrivate;

class HRbTableHeaderModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit HRbTableHeaderModel(int rows, int columns, QObject *parent = nullptr);
    ~HRbTableHeaderModel() override;

public:
    QModelIndex index(int row, int column, const QModelIndex & parent = QModelIndex()) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

protected:
    HRbTableHeaderModel(HRbTableHeaderModelPrivate &p, QObject *parent = nullptr);

protected:
    QScopedPointer<HRbTableHeaderModelPrivate> d_ptr;
};

HE_END_NAMESPACE
