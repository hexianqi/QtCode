/***************************************************************************************************
**      2019-05-08  HAbstractTableExtend 抽象表格视图扩展。
***************************************************************************************************/

#pragma once

#include "ITableExtend.h"
#include <QtUiPlugin/QDesignerExportWidget>
#include <QtCore/QObject>

class HAbstractTableExtendPrivate;

class HAbstractTableExtend : public QObject, public ITableExtend
{
    Q_OBJECT

public:
    explicit HAbstractTableExtend(QObject *parent = nullptr);
    ~HAbstractTableExtend() override;

public:
    void setTableView(QTableView *) override;
    QTableView *tableView() override;

protected:
    HAbstractTableExtend(HAbstractTableExtendPrivate &p, QObject *parent = nullptr);

protected:
    QScopedPointer<HAbstractTableExtendPrivate> d_ptr;
};
