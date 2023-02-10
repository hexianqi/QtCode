/***************************************************************************************************
**      2019-04-09  HResultTableWidget 结果表。
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include "HePlugin/HEntireTableWidget.h"

HE_BEGIN_NAMESPACE

class ITestData;
class HResultTableWidgetPrivate;

class HResultTableWidget : public HEntireTableWidget
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HResultTableWidget)

public:
    explicit HResultTableWidget(QWidget *parent = nullptr);
    ~HResultTableWidget() override;

public:
    void setDisplay(const QStringList &);
    void setSelected(const QStringList &);
    void setFixedRowCount(int);
    void clearResult();
    void refreshLast(bool append, ITestData *data = nullptr);
    void refreshRow(int row, ITestData *data = nullptr);

public:
    QStringList selected();

protected:
    HResultTableWidget(HResultTableWidgetPrivate &p, QWidget *parent = nullptr);

protected:
    void fillContents();
    void setRowBackgroundColor(int row, QVariantMap);

private:
    void init();
};

HE_END_NAMESPACE
