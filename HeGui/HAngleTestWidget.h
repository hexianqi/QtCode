/***************************************************************************************************
**      2022-04-06  HAngleTestWidget
***************************************************************************************************/

#pragma once

#include "HTestWidget.h"

HE_BEGIN_NAMESPACE

class HAngleTestWidgetPrivate;

class HAngleTestWidget : public HTestWidget
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HAngleTestWidget)

public:
    explicit HAngleTestWidget(QWidget *parent = nullptr);
    ~HAngleTestWidget() override;

public:
    QString typeName() override;

protected:
    void restoreState() override;
    void handleAction(HActionType action) override;
    void createAction() override;
    void createWidget() override;
    void createMenu() override;
    void createToolBar() override;
    void initWidget() override;
    void clearResult() override;
    void exportExcel() override;
    void handleStateChanged(bool b);
    void handleResultChanged(HActionType, bool);
    void exportDatabase();
    void printPreview();
};

HE_END_NAMESPACE

