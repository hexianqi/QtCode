/***************************************************************************************************
**      2019-04-22  HTestTable 表格测试。
***************************************************************************************************/

#ifndef HTESTTABLE_H
#define HTESTTABLE_H

#include "HControlGlobal.h"

class QTableView;
class QTableWidget;

HE_CONTROL_BEGIN_NAMESPACE

class HE_CONTROL_EXPORT HTestTable
{
public:
    static QTableView *multHeaderTableView();
    static QTableWidget *multHeaderTableWidget();
};

HE_CONTROL_END_NAMESPACE

#endif // HTESTTABLE_H
