/***************************************************************************************************
**      2021-01-26  HSpecTestWidget
***************************************************************************************************/

#pragma once

#include "HTestWidget.h"

HE_GUI_BEGIN_NAMESPACE

class HSpecTestWidgetPrivate;

class HE_GUI_EXPORT HSpecTestWidget : public HTestWidget
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HSpecTestWidget)

public:
    explicit HSpecTestWidget(QWidget *parent = nullptr);
    ~HSpecTestWidget() override;

public:
    void start() override;
    void stop() override;

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
    void exportExcel() override;
    void clearResult() override;

protected:
    virtual void readSettings();
    virtual void writeSettings();
    virtual void postProcess();
    virtual void refreshWidget(bool append);
    void handleStateChanged(bool);
    void handleSaveModeChanged(int);
    void handleResultChanged(HActionType, bool);
    void openCieDialog();
    void resetGrade();
    void exportDatabase();
    void printPreview();
    void removeResult();
    void setExportPath();
    void setSyncFile();
    void editQuantum();
    void editProduct();
};

HE_GUI_END_NAMESPACE

