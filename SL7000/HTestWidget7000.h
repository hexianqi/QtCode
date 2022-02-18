/***************************************************************************************************
**      2022-02-10  HTestWidget7000
***************************************************************************************************/

#pragma once

#include "HeGui/HTestWidget.h"

HE_USE_NAMESPACE

class HTestWidget7000Private;

class HTestWidget7000 : public HTestWidget
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HTestWidget7000)

public:
    explicit HTestWidget7000(QWidget *parent = nullptr);
    ~HTestWidget7000() override;

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
    void exportExcel() override;

protected:
    void readSettings();
    void writeSettings();
    void handleStateChanged(bool);
    void handleSaveModeChanged(int);
    void handleResultChanged(HActionType, bool);
    void resetGrade();
    void resetQuality();
    void resetLocation();
    void setProbe(bool b);
    void editProduct();
};



