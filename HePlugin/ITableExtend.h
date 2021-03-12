/***************************************************************************************************
**      2019-05-08  ITableExtend 表格视图扩展接口。
***************************************************************************************************/

#pragma once

class QTableView;

class ITableExtend
{
public:
    // 设置表格视图
    virtual void setTableView(QTableView *) = 0;
    // 关联的表格视图
    virtual QTableView *tableView() = 0;
};
