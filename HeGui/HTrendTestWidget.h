/***************************************************************************************************
**      2022-06-06  HTrendTestWidget
***************************************************************************************************/

#pragma once

#include "HTestWidget.h"

HE_BEGIN_NAMESPACE

class HTrendTestWidgetPrivate;

class HTrendTestWidget : public HTestWidget
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HTrendTestWidget)

public:
    explicit HTrendTestWidget(QWidget *parent = nullptr);
    ~HTrendTestWidget() override;

public:
    QString typeName() override;

protected:
    void createAction() override;
    void createWidget() override;
    void createMenu() override;
    void createToolBar() override;
    void initWidget() override;
    void clearResult() override;
    void exportExcel() override;
    void readSettings() override;
    void writeSettings() override;
    void changeDisplay(QAction *);
    void handleStateChanged(bool);
    void handleResultChanged(HActionType, bool);
};

HE_END_NAMESPACE

