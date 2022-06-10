/***************************************************************************************************
**      2021-01-26  HSpecTestWidget
***************************************************************************************************/

#pragma once

#include "HTestWidget.h"

HE_BEGIN_NAMESPACE

class HSpecTestWidgetPrivate;

class HSpecTestWidget : public HTestWidget
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HSpecTestWidget)

public:
    explicit HSpecTestWidget(QWidget *parent = nullptr);
    ~HSpecTestWidget() override;

protected:
    HSpecTestWidget(HSpecTestWidgetPrivate &p, QWidget *parent = nullptr);

protected:
    void init() override;
    void closeEvent(QCloseEvent *) override;
    void handleAction(HActionType action) override;
    void createAction() override;
    void createWidget() override;
    void createMenu() override;
    void createToolBar() override;
    void initWidget() override;
    void clearResult() override;
    void saveResult() override;
    void exportExcel() override;
    void readSettings() override;
    void writeSettings() override;

protected:

    virtual void postProcess(bool append);
    virtual void refreshWidget(bool append);
    void handleStateChanged(bool);
    void handleSaveModeChanged(int);
    void handleResultChanged(HActionType, bool);
    void exportExcelAppend();
    void exportDatabase();
    void exportDatabaseRange(int index, int count);
    void exportDatabaseLast();
    void printPreview();
    void printTag();
    void resetSpec();
    void resetGrade();
    void openCieDialog();
    void removeResult();
    void setExportPath();
    void setSyncFile();
    void editProduct();
};

HE_END_NAMESPACE

