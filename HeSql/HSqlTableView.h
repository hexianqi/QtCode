/***************************************************************************************************
**      2019-05-09  HSqlTableView
***************************************************************************************************/

#ifndef HSQLTABLEVIEW_H
#define HSQLTABLEVIEW_H

#include "HSqlGlobal.h"
#include "HePlugin/HTableView.h"

HE_SQL_BEGIN_NAMESPACE

class ISqlTableModel;
class HSqlTableViewPrivate;

class HSqlTableView : public HTableView
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HSqlTableView)

public:
    explicit HSqlTableView(QWidget *parent = nullptr);
    ~HSqlTableView() override;

public:
    void setModel(ISqlTableModel *);

private:
    void init();
    using HTableView::setModel;
};

HE_SQL_END_NAMESPACE

#endif // HSQLTABLEVIEW_H
