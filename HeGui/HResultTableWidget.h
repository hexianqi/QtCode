/***************************************************************************************************
**      2019-04-09  HResultTableWidget 结果表。
***************************************************************************************************/

#pragma once

#include "HGuiGlobal.h"
#include "HePlugin/HEntireTableWidget.h"

HE_GUI_BEGIN_NAMESPACE

class HResultTableWidgetPrivate;

class HE_GUI_EXPORT HResultTableWidget : public HEntireTableWidget
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HResultTableWidget)

public:
    explicit HResultTableWidget(QWidget *parent = nullptr);
    ~HResultTableWidget() override;

public:
    void setDisplay(const QStringList &value);
    void setSelected(const QStringList &value);
    void clearResult();
    void refreshResult(bool append);

public:
    QStringList selected();

protected:
    HResultTableWidget(HResultTableWidgetPrivate &p, QWidget *parent = nullptr);

private:
    void init();
};

HE_GUI_END_NAMESPACE
