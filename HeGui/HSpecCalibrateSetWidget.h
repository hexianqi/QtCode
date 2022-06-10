/***************************************************************************************************
**      2019-04-11  HSpecCalibrateSetWidget 光谱校准设置窗体。
***************************************************************************************************/

#pragma once

#include "HAbstractTestSetWidget.h"

namespace Ui {
class HSpecCalibrateSetWidget;
}

HE_BEGIN_NAMESPACE

class HSpecCalibrateSetWidgetPrivate;

class HSpecCalibrateSetWidget : public HAbstractTestSetWidget
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HSpecCalibrateSetWidget)

public:
    explicit HSpecCalibrateSetWidget(QWidget *parent = nullptr);
    ~HSpecCalibrateSetWidget() override;

public:
    QString typeName() override;

public:
    void handleAction(HActionType action) override;
    bool setTestState(bool b) override;
    bool setTestMode(int value) override;

protected slots:
    void setAutoIntegralTime(bool b);
    void on_checkBox_01_clicked(bool b);
    void on_checkBox_02_clicked(bool b);
    void on_radioButton_01_clicked();
    void on_radioButton_02_clicked();

protected:
    bool adjustIntegralTime();

private:
    void init();

private:
    Ui::HSpecCalibrateSetWidget *ui;
};

HE_END_NAMESPACE
