/***************************************************************************************************
**      2019-05-08  ITableExtend 表格视图扩展接口。
***************************************************************************************************/

#ifndef ITABLEEXTEND_H
#define ITABLEEXTEND_H

class QTableView;

class ITableExtend
{
public:
    // 设置表格视图
    virtual void setTableView(QTableView *) = 0;
    // 关联的表格视图
    virtual QTableView *tableView() = 0;
};

#endif // ITABLEEXTEND_H
