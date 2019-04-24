/***************************************************************************************************
**      2019-04-22  HTestTable 表格测试。
***************************************************************************************************/

#ifndef HTESTTABLE_H
#define HTESTTABLE_H

#include "HExampleGlobal.h"

class QTableView;
class QTableWidget;

class HE_EXAMPLE_EXPORT HTestTable
{
public:
    static QTableView *multHeaderTableView();
    static QTableWidget *multHeaderTableWidget();
};

#endif // HTESTTABLE_H
