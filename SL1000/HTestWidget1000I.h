/***************************************************************************************************
**      2023-03-29  HTestWidget1000I
***************************************************************************************************/

#pragma once

#include "HeGui/HTestWidget.h"

HE_USE_NAMESPACE

class HTestWidget1000IPrivate;

class HTestWidget1000I : public HTestWidget
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HTestWidget1000I)

public:
    explicit HTestWidget1000I(QWidget *parent = nullptr);
    ~HTestWidget1000I() override;

public:
    QString typeName() override;

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
//    virtual void postProcess(bool append);
//    virtual void refreshWidget(bool append);
//    void handleStateChanged(bool);
//    void handleSaveModeChanged(int);
//    void handleResultChanged(HActionType, bool);
//    void exportExcelAppend();
//    void exportDatabase();
//    void exportDatabaseRange(int index, int count);
//    void exportDatabaseLast();
//    void printPreview();
//    void printTag();
//    void resetSpec();
//    void resetGrade();
//    void openCieDialog();
//    void removeResult();
//    void setExportPath();
//    void setSyncFile();
//    void editProduct();
};
