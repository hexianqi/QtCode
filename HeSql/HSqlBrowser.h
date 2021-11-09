/***************************************************************************************************
**      2019-05-09  HSqlBrowser 数据库浏览器。
***************************************************************************************************/

#pragma once

#include "ISqlBrowser.h"

HE_SQL_BEGIN_NAMESPACE

class HSqlBrowserPrivate;

class HE_SQL_EXPORT HSqlBrowser : public ISqlBrowser
{
    Q_OBJECT

public:
    explicit HSqlBrowser(QWidget *parent = nullptr);
    ~HSqlBrowser() override;

public:
    void initialize(QVariantMap param) override;
    QString typeName() override;

public:
    void setModel(ISqlTableModel *) override;
    void setRecordHandle(ISqlHandle *) override;
    void setRecordOutput(ISqlOutput *) override;
    void revert() override;

protected:
    HSqlBrowser(HSqlBrowserPrivate &p, QWidget *parent = nullptr);

protected:
    void removeRecord();
    void exportExcel();

protected:
    QScopedPointer<HSqlBrowserPrivate> d_ptr;

private:
    void init();
    void createAction();
    void createToolBar();
    void createTableView();
    void createLayout();
};

HE_SQL_END_NAMESPACE
