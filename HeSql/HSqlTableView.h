/***************************************************************************************************
**      2019-05-09  HSqlTableView
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include "HePlugin/HTableView.h"

HE_BEGIN_NAMESPACE

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

HE_END_NAMESPACE
